/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpiven <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 00:03:20 by tpiven            #+#    #+#             */
/*   Updated: 2018/01/22 00:03:24 by tpiven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	parse_flags(const char *format, t_form *frt, size_t i)
{
	if (format[i] == '#')
		frt->hash = '#';
	if (format[i] == ' ')
		frt->space = ' ';
	if (format[i] == '-')
		frt->minus = '-';
	if (format[i] == '+')
		frt->plus = '+';
	if (format[i] == '0')
		frt->zero = '0';
	i++;
	return (i);
}

size_t	parse_flags_size(const char *format, t_form *frt, size_t i)
{
	if (format[i] == 'h')
	{
		if (format[i + 1] == 'h' && frt->flagsize < 1)
			frt->flagsize = 1;
		else if (frt->flagsize < 2)
			frt->flagsize = 2;
	}
	if (format[i] == 'l')
	{
		if (format[i + 1] == 'l' && (frt->flagsize < 4))
			frt->flagsize = 4;
		else if (frt->flagsize < 3)
			frt->flagsize = 3;
	}
	if (format[i] == 'j' && frt->flagsize < 5)
		frt->flagsize = 5;
	if (format[i] == 'z' && frt->flagsize < 6)
		frt->flagsize = 6;
	if (format[i] == 't' && frt->flagsize < 7)
		frt->flagsize = 7;
	if (frt->flagsize == 4 || frt->flagsize == 1)
		i = i + 2;
	else
		i++;
	return (i);
}

size_t	parse_precis(const char *format, t_form *frt, va_list *ap, size_t i)
{
	i++;
	frt->has_prec = 1;
	if (format[i] == '*')
	{
		i++;
		frt->prec = va_arg(&(**ap), int);
		if (frt->prec < 0)
			frt->has_prec = 0;
	}
	else
	{
		frt->prec = 0;
		while (ft_isdigit(format[i]))
		{
			frt->prec = frt->prec * 10 + (format[i] - '0');
			i++;
		}
	}
	return (i);
}

size_t	parse_width(const char *format, t_form *frt, va_list *ap, size_t i)
{
	if (format[i] == '*')
	{
		i++;
		frt->width = va_arg(&(**ap), int);
		if (frt->width < 0)
		{
			frt->width = -frt->width;
			frt->minus = '-';
		}
	}
	if (ft_isdigit(format[i]) && format[i] != '0')
	{
		frt->width = 0;
		while (ft_isdigit(format[i]))
		{
			frt->width = frt->width * 10 + (format[i] - '0');
			i++;
		}
	}
	return (i);
}
