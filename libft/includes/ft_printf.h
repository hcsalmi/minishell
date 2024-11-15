/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:50:10 by esirnio           #+#    #+#             */
/*   Updated: 2023/07/06 17:21:23 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

typedef struct s_print
{
	va_list				args;
	int					width;
	const char			*s;
	int					ind;
	int					spec_width;
	char				specifier;
	int					print_zero;
	long double			float_arg;
	int					rounding;
	int					printlen;
	int					upper_l;
	int					hash;
	int					left;
	int					plus;
	int					space;
	int					pad;
	int					prec;
	int					helper;
	int					zeros;
	long long			ll_d;
	unsigned long long	unsigned_arg;
	char				*print;
	int					l;
	int					ll;
	int					h;
	int					hh;
	int					cap;
	int					sign;
	int					minus;
	int					filled;
}						t_print;

int		ft_printf(const char *fmt, ...);
void	start_values(t_print *var);
void	set_values(t_print *var);
int		check_conversion(t_print *var);
void	check_flags(t_print *var);
void	check_width_and_precision(t_print *var);
void	check_width(t_print *var);
void	check_precision(t_print *var);
void	length_modifier(t_print *var);
int		check_specifier(t_print *var);

/*float*/
void	do_float(t_print *var);
void	get_float_arg(t_print *var);
void	float_plus_minus(t_print *var);
void	check_decimals(t_print *var);
void	get_rounded(t_print *var);
void	print_float(t_print *var, long long value);
void	print_value(t_print *var, long long value);
void	bigger_width_float(t_print *var, long long value);
void	fill_width_float(t_print *var, int num, char pad);

/*di*/
void	do_integer(t_print *var, int base);
void	get_int_arg(t_print *var, int base);
void	plusflag_or_negative(t_print *var);
void	print_zero(t_print *var);
void	print_integer(t_print *var, char *string);
void	fill_before_sign_int(t_print *var, int len);
void	bigger_width_int(t_print *var, char *string);
void	check_fill(t_print	*var);
void	fill_width_int(t_print *var, int num, char pad);

/*common*/
void	hash_and_zeros(t_print *var);
void	ft_putnstr(char const *str, int n, t_print *var);
void	print_conversion(t_print *var, char *string);
void	fill_width(t_print *var, int num, char pad);
void	hash(t_print	*var);
void	bigger_width(t_print *var, char *string);

/*%,c,s*/
void	do_modulo(t_print *var);
void	do_string(t_print *var);
void	do_char(t_print *var);
void	move_left(t_print *var);
void	add_to_print(t_print *var, int ch);

/*xXpou*/
void	get_unsigned_arg(t_print *var, int base);
void	do_hexa(t_print	*var, int base);
void	unsigned_zero(t_print *var);
void	print_zero(t_print *var);
void	do_hexa(t_print *var, int base);
void	do_unsigned(t_print	*var, int base);
char	*ft_itoa_uns(unsigned long long value, int base, int capital);

#endif
