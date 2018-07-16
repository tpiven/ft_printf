/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_spec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpiven <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:07:10 by tpiven            #+#    #+#             */
/*   Updated: 2018/01/31 17:07:12 by tpiven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_conv_d(va_list *ap, t_form *frt)
{
	if (frt->flagsize == 1)
		frt->str = ft_itoa((char)va_arg(&(**ap), void*));
	if (frt->flagsize == 2)
		frt->str = ft_itoa((short)va_arg(&(**ap), void*));
	if (frt->flagsize == 0)
		frt->str = ft_itoa((int)va_arg(&(**ap), void*));
	if (frt->flagsize == 3)
		frt->str = ft_itoa((long)va_arg(&(**ap), void*));
	if (frt->flagsize == 4)
		frt->str = ft_itoa((long long)va_arg(&(**ap), void*));
	if (frt->flagsize == 5)
		frt->str = ft_itoa((intmax_t)va_arg(&(**ap), void*));
	if (frt->flagsize == 6)
		frt->str = ft_itoa((ssize_t)va_arg(&(**ap), void*));
	if (frt->flagsize == 7)
		frt->str = ft_itoa((ptrdiff_t)va_arg(&(**ap), void*));
}

void	ft_conv_o(va_list *ap, t_form *frt)
{
	if (frt->flagsize == 1)
		frt->str = ft_itoa_base((unsigned char)va_arg(&(**ap), void*), 8);
	if (frt->flagsize == 2)
		frt->str = ft_itoa_base((unsigned short)va_arg(&(**ap), void*), 8);
	if (frt->flagsize == 0)
		frt->str = ft_itoa_base((unsigned int)va_arg(&(**ap), void*), 8);
	if (frt->flagsize == 3)
		frt->str = ft_itoa_base((unsigned long)va_arg(&(**ap), void*), 8);
	if (frt->flagsize == 4)
		frt->str = ft_itoa_base((unsigned long long)va_arg(&(**ap), void*), 8);
	if (frt->flagsize == 5)
		frt->str = ft_itoa_base((uintmax_t)va_arg(&(**ap), void*), 8);
	if (frt->flagsize == 6)
		frt->str = ft_itoa_base((size_t)va_arg(&(**ap), void*), 8);
	if (frt->flagsize == 7)
		frt->str = ft_itoa_base((uintptr_t)va_arg(&(**ap), void*), 8);
}

void	ft_conv_u(va_list *ap, t_form *frt)
{
	if (frt->flagsize == 1)
		frt->str = ft_itoa_base((unsigned char)va_arg(&(**ap), void*), 10);
	if (frt->flagsize == 2)
		frt->str = ft_itoa_base((unsigned short)va_arg(&(**ap), void*), 10);
	if (frt->flagsize == 0)
		frt->str = ft_itoa_base((unsigned int)va_arg(&(**ap), void*), 10);
	if (frt->flagsize == 3)
		frt->str = ft_itoa_base((unsigned long)va_arg(&(**ap), void*), 10);
	if (frt->flagsize == 4)
		frt->str = ft_itoa_base((unsigned long long)va_arg(&(**ap), void*), 10);
	if (frt->flagsize == 5)
		frt->str = ft_itoa_base((uintmax_t)va_arg(&(**ap), void*), 10);
	if (frt->flagsize == 6)
		frt->str = ft_itoa_base((size_t)va_arg(&(**ap), void*), 10);
	if (frt->flagsize == 7)
		frt->str = ft_itoa_base((uintptr_t)va_arg(&(**ap), void*), 10);
}

void	ft_conv_x(va_list *ap, t_form *frt, size_t i)
{
	if (frt->flagsize == 1)
		frt->str = ft_itoa_base((unsigned char)va_arg(&(**ap), void*), 16);
	if (frt->flagsize == 2)
		frt->str = ft_itoa_base((unsigned short)va_arg(&(**ap), void*), 16);
	if (frt->flagsize == 0)
		frt->str = ft_itoa_base((unsigned int)va_arg(&(**ap), void*), 16);
	if (frt->flagsize == 3)
		frt->str = ft_itoa_base((unsigned long)va_arg(&(**ap), void*), 16);
	if (frt->flagsize == 4)
		frt->str = ft_itoa_base((unsigned long long)va_arg(&(**ap), void*), 16);
	if (frt->flagsize == 5)
		frt->str = ft_itoa_base((uintmax_t)va_arg(&(**ap), void*), 16);
	if (frt->flagsize == 6)
		frt->str = ft_itoa_base((size_t)va_arg(&(**ap), void*), 16);
	if (frt->flagsize == 7)
		frt->str = ft_itoa_base((uintptr_t)va_arg(&(**ap), void*), 16);
	if (frt->spec == 'X')
		while (frt->str[i] != '\0')
		{
			frt->str[i] = ft_toupper(frt->str[i]);
			i++;
		}
	if (frt->str[0] == '0')
		frt->hash = '\0';
}

void	ft_conv_c(va_list *ap, t_form *frt)
{
	if (frt->flagsize == 3)
		frt->spec = 'C';
	else
	{
		frt->str = ft_strnew(1);
		frt->str[0] = (int)va_arg(&(**ap), void*);
		if (frt->str[0] == 0)
		{
			frt->symb = '\0';
			frt->len = 1;
			if (frt->width != 0)
				frt->width -= 1;
		}
	}
}
