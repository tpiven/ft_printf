/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpiven <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 16:58:39 by tpiven            #+#    #+#             */
/*   Updated: 2018/01/17 16:58:41 by tpiven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../libft/libft.h"

# define SPEC_NUMB(x)  SPEC_SNUMB(x) || SPEC_XO(x) || x == 'u' || x == 'U'
# define SPEC_XO(x) x == 'o' || x == 'O' || x == 'x' || x == 'X' || x == 'p'
# define SPEC_SNUMB(x)  x == 'd' || x == 'D' || x == 'i'
# define SPEC(x) x == 's' || x == 'S' || x == 'c' || x == 'C'
# define FLAGS(x) x == '0' || x == '+' || x == '-' || x == '#' || x == ' '
# define FLAGS_SIZE(x) x == 'l' || x == 'h' || x == 'j' || x == 'z' || x == 't'
# define INVALID(x) INV1(x) && INV2(x) && INV3(x) && INV4(x) && INV5(x) && IV(x)
# define INV1(x) x != 's' && x != 'S' && x != 'p' && x != 'd' && x != 'D'
# define INV2(x) x != 'i' && x != 'o' && x != 'O' && x != 'u' && x != 'U'
# define INV3(x) x != 'x' && x != 'X' && x != 'c' && x != 'C' && x != '0'
# define INV4(x) x != '+' && x != '-' && x != '#' && x != ' ' && x != 'l'
# define INV5(x) x != 'h' && x != 'j' && x != 'z' && x != '.' && x != '*'
# define IV(x) x != 't'
# define SYMBOLS(x) x != '+' && x != '-' && x != 'x' && x != 'X' && x != ' '

typedef struct		s_form
{
	size_t			has_prec;
	size_t			flagsize;
	int				len;
	char			zero;
	char			hash;
	char			space;
	char			plus;
	char			minus;
	char			symb;
	char			spec;
	char			*str;
	int				width;
	int				prec;
	int				setloc;
	unsigned int	chr;
	unsigned int	*arr;
}					t_form;

typedef struct		s_len
{
	int				i;
	int				len;
	int				j;
	int				l;
}					t_len;

int					ft_printf(const char *format, ...);
int					ft_analitic(va_list *ap, const char *format, t_form *frt,\
								t_len *n);
int					ft_parse_format(const char *format, t_form *frt,\
										va_list *ap, size_t i);
int					ft_print_lcs(t_form *frt);
int					ft_print_lc(t_form *frt);
int					ft_print_ls(t_form *frt);
int					ft_print(va_list *ap, t_form *frt);

void				init_struct(t_form *frt);
void				ft_init_n(t_len *n);
void				ft_handle_prec(t_form *frt);
void				ft_handle_widthx(t_form *frt);
void				ft_handle_width(t_form *frt);
void				ft_conv_sp(va_list *ap, t_form *frt);
void				ft_handle_plh(t_form *frt);
void				ft_conv_d(va_list *ap, t_form *frt);
void				ft_conv_o(va_list *ap, t_form *frt);
void				ft_conv_u(va_list *ap, t_form *frt);
void				ft_conv_x(va_list *ap, t_form *frt, size_t i);
void				ft_conv_c(va_list *ap, t_form *frt);
void				ft_handle_spec(va_list *ap, t_form *frt);
void				ft_handle_wchar(va_list *ap, t_form *frt);
void				ft_prec_wstr(t_form *frt, size_t j, wchar_t *str);
void				ft_audit_setloc(t_form *frt);
void				ft_handle_wstr(va_list *ap, t_form *frt);

size_t				parse_flags(const char *format, t_form *frt, size_t i);
size_t				parse_flags_size(const char *format, t_form *frt, size_t i);
size_t				parse_precis(const char *format, t_form *frt, va_list *ap,\
									size_t i);
size_t				parse_width(const char *format, t_form *frt, va_list *ap,\
								size_t i);
size_t				ft_wcharlen(wchar_t chr);

#endif
