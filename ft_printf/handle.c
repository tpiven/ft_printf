/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpiven <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:23:05 by tpiven            #+#    #+#             */
/*   Updated: 2018/01/30 19:23:07 by tpiven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_handle_prec(t_form *frt)
{
	char	*temp;
	int		i;
	int		len;

	i = 0;
	len = (int)ft_strlen(frt->str);
	if (frt->str[0] == '-')
		len = (int)ft_strlen(frt->str) - 1;
	if ((frt->prec > len) && (SPEC_NUMB(frt->spec) || frt->spec == 'p'))
	{
		temp = ft_strnew(frt->prec - len);
		while (i < frt->prec - len)
			temp[i++] = '0';
		if (frt->str[0] == '-')
		{
			temp[0] = frt->str[0];
			frt->str[0] = '0';
		}
		frt->str = ft_newstr(temp, frt->str);
	}
	if ((frt->spec == 's' || frt->spec == 'S') && frt->prec < len)
		frt->str[frt->prec] = '\0';
	if (frt->prec == 0 && frt->str[0] == '0' && ft_strlen(frt->str) == 1)
		frt->str[0] = '\0';
}

void	ft_handle_widthx(t_form *frt)
{
	size_t i;

	i = 0;
	while (SYMBOLS(frt->str[i]))
		i++;
	if (frt->str[i] == '-')
		frt->str[0] = '-';
	if (frt->str[i] == '+')
		frt->str[0] = '+';
	if (frt->str[i] == 'x')
		frt->str[1] = 'x';
	if (frt->str[i] == 'X')
		frt->str[1] = 'X';
	if (frt->str[i] == ' ')
		frt->str[0] = ' ';
	frt->str[i] = '0';
}

void	ft_handle_width(t_form *frt)
{
	char	*temp;
	size_t	i;

	i = frt->width - ft_strlen(frt->str);
	temp = ft_strnew(frt->width - ft_strlen(frt->str));
	if (frt->zero == '0' && frt->minus != '-' && (frt->has_prec == 0 ||\
		(((SPEC(frt->spec)) || frt->spec == '\0') && frt->has_prec != 0)))
		ft_memset((void*)temp, '0', i);
	else
		ft_memset((void*)temp, ' ', i);
	if (frt->minus == '-')
		frt->str = ft_newstr(frt->str, temp);
	else
		frt->str = ft_newstr(temp, frt->str);
	if (frt->zero == '0' && frt->minus != '-' && frt->has_prec == 0 &&\
		(ft_strchr(frt->str, '-') || ft_strchr(frt->str, '+') ||\
		ft_strchr(frt->str, 'x') || ft_strchr(frt->str, 'X') ||\
		ft_strchr(frt->str, ' ')) && (SPEC_NUMB(frt->spec)))
		ft_handle_widthx(frt);
}

void	ft_conv_sp(va_list *ap, t_form *frt)
{
	char *temp;

	if (frt->spec == 's')
	{
		if (frt->flagsize == 3)
			frt->spec = 'S';
		else
		{
			frt->str = ft_strdup((char *)va_arg(&(**ap), char*));
			if (frt->str == NULL)
				frt->str = ft_strdup("(null)");
		}
	}
	if (frt->spec == 'p')
	{
		frt->str = ft_itoa_base((unsigned long long)va_arg(&(**ap), void*), 16);
		if (frt->has_prec != 0)
			ft_handle_prec(frt);
		temp = ft_strdup("0x");
		frt->str = ft_newstr(temp, frt->str);
	}
}

void	ft_handle_plh(t_form *frt)
{
	char *temp;

	temp = NULL;
	if ((frt->plus == '+' || frt->space == ' ') &&\
		(SPEC_SNUMB(frt->spec)) && frt->str[0] != '-')
	{
		if (frt->plus == '+')
			temp = ft_strdup("+");
		if (frt->space == ' ' && frt->plus != '+')
			temp = ft_strdup(" ");
		frt->str = ft_newstr(temp, frt->str);
	}
	if (frt->hash == '#' && (frt->spec == 'o' || frt->spec == 'O'\
		|| frt->spec == 'x' || frt->spec == 'X'))
	{
		if ((frt->spec == 'o' || frt->spec == 'O') && frt->str[0] != '0')
			temp = ft_strdup("0");
		if (frt->spec == 'x')
			temp = ft_strdup("0x");
		if (frt->spec == 'X')
			temp = ft_strdup("0X");
		frt->str = ft_newstr(temp, frt->str);
	}
}
