/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpiven <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 00:03:34 by tpiven            #+#    #+#             */
/*   Updated: 2018/01/22 00:03:36 by tpiven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_handle_spec(va_list *ap, t_form *frt)
{
	if (frt->spec == 'd' || frt->spec == 'i')
		ft_conv_d(&(*ap), frt);
	if (frt->spec == 'u')
		ft_conv_u(&(*ap), frt);
	if (frt->spec == 'o')
		ft_conv_o(&(*ap), frt);
	if (frt->spec == 'x' || frt->spec == 'X')
		ft_conv_x(&(*ap), frt, 0);
	if (frt->spec == 'D')
		frt->str = ft_itoa((long)va_arg(&(**ap), void*));
	if (frt->spec == 'O')
		frt->str = ft_itoa_base((unsigned long)va_arg(&(**ap), void*), 8);
	if (frt->spec == 'U')
		frt->str = ft_itoa_base((unsigned long)va_arg(&(**ap), void*), 10);
	if (frt->spec == 's' || frt->spec == 'p')
		ft_conv_sp(&(*ap), frt);
	if (frt->spec == 'c')
		ft_conv_c(&(*ap), frt);
	if (frt->spec == 'C')
		ft_handle_wchar(&(*ap), frt);
	if (frt->spec == 'S')
		ft_handle_wstr(&(*ap), frt);
}

int		ft_print_lcs(t_form *frt)
{
	int len;

	if (frt->minus == '-')
	{
		ft_putwchar(frt->chr);
		ft_putstr(frt->str);
	}
	else
	{
		ft_putstr(frt->str);
		ft_putwchar(frt->chr);
	}
	len = (int)(ft_strlen(frt->str) + frt->len);
	ft_strdel(&frt->str);
	return (len);
}

int		ft_print_lc(t_form *frt)
{
	int len;

	if (frt->minus == '-')
	{
		ft_putchar(frt->chr);
		ft_putstr(frt->str);
	}
	else
	{
		ft_putstr(frt->str);
		ft_putchar(frt->chr);
	}
	len = (int)(ft_strlen(frt->str) + frt->len);
	ft_strdel(&frt->str);
	return (len);
}

int		ft_print_ls(t_form *frt)
{
	int len;

	if (frt->minus == '-')
	{
		ft_putwstr(frt->arr);
		ft_putstr(frt->str);
	}
	else
	{
		ft_putstr(frt->str);
		ft_putwstr(frt->arr);
	}
	len = (int)(ft_strlen(frt->str) + frt->len);
	ft_strdel(&frt->str);
	free(frt->arr);
	return (len);
}

int		ft_print(va_list *ap, t_form *frt)
{
	int len;

	if (SPEC_NUMB(frt->spec) || SPEC(frt->spec))
		ft_handle_spec(&(*ap), frt);
	if (frt->has_prec != 0)
		ft_handle_prec(frt);
	if (frt->plus == '+' || frt->hash == '#' || frt->space == ' ')
		ft_handle_plh(frt);
	if (frt->width > (int)ft_strlen(frt->str))
		ft_handle_width(frt);
	if (frt->spec == 'C' && frt->setloc != -1)
		return (ft_print_lcs(frt));
	if ((frt->spec == 'C' && frt->setloc == -1) || frt->symb == 0)
		return (ft_print_lc(frt));
	if (frt->setloc == -1)
	{
		ft_strdel(&frt->str);
		return (-1);
	}
	if (frt->spec == 'S' && frt->arr != NULL)
		return (ft_print_ls(frt));
	ft_putstr(frt->str);
	len = (int)ft_strlen(frt->str);
	ft_strdel(&frt->str);
	return (len);
}
