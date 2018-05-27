/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpiven <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 16:58:51 by tpiven            #+#    #+#             */
/*   Updated: 2018/01/17 16:58:52 by tpiven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_init_n(t_len *n)
{
	n->i = 0;
	n->j = 0;
	n->len = 0;
	n->l = 0;
}

void	init_struct(t_form *frt)
{
	frt->has_prec = 0;
	frt->flagsize = 0;
	frt->zero = '\0';
	frt->hash = '\0';
	frt->space = '\0';
	frt->plus = '\0';
	frt->minus = '\0';
	frt->symb = '+';
	frt->spec = '\0';
	frt->str = NULL;
	frt->width = 0;
	frt->prec = 0;
	frt->len = 0;
	frt->setloc = 0;
	frt->chr = 0;
	frt->arr = NULL;
}

int		ft_parse_format(const char *format, t_form *frt, va_list *ap, size_t i)
{
	init_struct(frt);
	while (format[i] != '\0')
	{
		if (FLAGS(format[i]))
			i = parse_flags(format, frt, i);
		if (FLAGS_SIZE(format[i]))
			i = parse_flags_size(format, frt, i);
		if (format[i] == '.')
			i = parse_precis(format, frt, &(*ap), i);
		if (format[i] == '*' || (ft_isdigit(format[i]) && format[i] != '0'))
			i = parse_width(format, frt, &(*ap), i);
		if (SPEC_NUMB(format[i]) || SPEC(format[i]))
		{
			frt->spec = format[i];
			break ;
		}
		if (INVALID(format[i]) && !ft_isdigit(format[i]))
		{
			frt->str = ft_strnew(1);
			frt->str[0] = format[i];
			break ;
		}
	}
	return ((int)i);
}

int		ft_analitic(va_list *ap, const char *format, t_form *frt, t_len *n)
{
	while (format[n->i] != '\0')
	{
		if (format[n->i] == '%')
		{
			ft_putnstr(&format[n->j], n->i - n->j);
			n->len = n->len + (n->i - n->j);
			if (format[n->i + 1] == '\0')
				break ;
			n->i = ft_parse_format(format, frt, &(*ap), (n->i + 1));
			n->j = n->i + 1;
			n->l = ft_print(&(*ap), frt);
			n->len = n->len + n->l;
			if (n->l == -1)
				return (-1);
		}
		if (format[n->i] == '\0')
			break ;
		if (format[n->i + 1] == '\0')
		{
			ft_putnstr(&format[n->j], n->i - n->j + 1);
			n->len = n->len + (n->i - n->j + 1);
		}
		n->i++;
	}
	return (n->len);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	int			len;
	t_form		*frt;
	t_len		*n;

	if (!ft_strchr(format, '%'))
	{
		ft_putstr(format);
		return ((int)ft_strlen(format));
	}
	va_start(ap, format);
	n = (t_len *)malloc(sizeof(t_len));
	ft_init_n(n);
	frt = (t_form *)malloc(sizeof(t_form));
	len = ft_analitic(&ap, format, frt, n);
	free(frt);
	free(n);
	va_end(ap);
	return (len);
}
