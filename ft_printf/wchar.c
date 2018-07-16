/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpiven <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 20:23:55 by tpiven            #+#    #+#             */
/*   Updated: 2018/01/30 20:23:56 by tpiven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		ft_wcharlen(wchar_t chr)
{
	size_t		i;

	i = 0;
	if (chr <= 127)
		i = 1;
	else if (chr <= 2047)
		i = 2;
	else if (chr <= 65535)
		i = 3;
	else
		i = 4;
	return (i);
}

void		ft_handle_wchar(va_list *ap, t_form *frt)
{
	frt->str = ft_strnew(1);
	frt->chr = (unsigned int)va_arg(&(**ap), void*);
	frt->len = (int)ft_wcharlen(frt->chr);
	if (MB_CUR_MAX <= 1)
	{
		frt->setloc = -1;
		frt->len = 1;
	}
	if (frt->width != 0 && frt->width > frt->len)
		frt->width = frt->width - frt->len;
	else if (frt->width != 0 && frt->width <= frt->len)
		frt->width = 0;
}

void		ft_prec_wstr(t_form *frt, size_t j, wchar_t *str)
{
	size_t		i;

	i = 0;
	if (frt->has_prec != 0)
	{
		while (frt->len <= frt->prec && i < j)
		{
			frt->len = frt->len + (int)ft_wcharlen(str[i]);
			if (frt->len <= frt->prec)
				frt->arr[i] = (unsigned int)str[i];
			i++;
		}
		if (frt->len > frt->prec)
			frt->len = frt->len - (int)ft_wcharlen(str[i - 1]);
	}
	else
	{
		while (i < j)
		{
			frt->arr[i] = (unsigned int)str[i];
			frt->len = frt->len + (int)ft_wcharlen(str[i]);
			i++;
		}
	}
}

void		ft_audit_setloc(t_form *frt)
{
	size_t		i;

	i = 0;
	if (MB_CUR_MAX <= 1)
		while (frt->arr[i] != 0)
        {
			if (frt->arr[i] > 127)
			{
				frt->setloc = -1;
				free(frt->arr);
				return ;
			}
            i++;
        }
    
}

void		ft_handle_wstr(va_list *ap, t_form *frt)
{
	wchar_t		*str;
	size_t		j;

	j = 0;
	str = va_arg(&(**ap), wchar_t*);
	if (str == NULL)
	{
		frt->str = ft_strdup("(null)");
		return ;
	}
	else
		frt->str = ft_strnew(1);
	while (str[j] != 0)
		j++;
	frt->arr = (unsigned int*)malloc(sizeof(unsigned int) * (j + 1));
	ft_bzero((void *)frt->arr, (j + 1) * sizeof(int));
	ft_prec_wstr(frt, j, str);
	if (frt->width != 0 && frt->width > frt->len)
		frt->width = frt->width - frt->len;
	else if (frt->width != 0 && frt->width <= frt->len)
		frt->width = 0;
	ft_audit_setloc(frt);
}
