/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:57:05 by esirnio           #+#    #+#             */
/*   Updated: 2023/07/06 17:10:33 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	get_int_arg(t_print *var, int base)
{
	char	*value;

	if (var->ll == 1)
		var->ll_d = (long long)va_arg(var->args, long long);
	else if (var->l == 1)
		var->ll_d = (long)va_arg(var->args, long);
	else if (var->h == 1)
		var->ll_d = (short)va_arg(var->args, int);
	else if (var->hh == 1)
		var->ll_d = (signed char)va_arg(var->args, int);
	else
		var->ll_d = (int)va_arg(var->args, int);
	value = ft_itoa_base((long long)var->ll_d, base);
	var->print = (char *)malloc(sizeof(char) * ft_strlen(value) + 1);
	if (!var->print)
		exit(-1);
	ft_strcpy(var->print, value);
}

void	plusflag_or_negative(t_print *var)
{
	int	len;

	len = ft_strlen(var->print) + var->plus + var->zeros;
	if (ft_strlen(var->print) == 0)
		len++;
	fill_before_sign_int(var, len);
	if (var->ll_d < 0)
	{
		var->width += write(1, "-", 1);
		var->minus = 1;
	}
	else if (var->plus == 1)
		var->width += write(1, "+", 1);
	if (var->left == 0 && (var->spec_width > (len - (var->ll_d < 0))))
		var->zeros++;
	var->space = 0;
	var->plus = 0;
	var->hash = 0;
	var->sign = 1;
}

void	is_zero(t_print *var)
{
	if (var->space == 1)
		var->width += write (1, " ", 1);
	if (var->ll_d == 0 && var->pad == '0' && var->left == 0 && var->prec == -1)
		return ;
	if (var->pad == '0' && var->prec == -1 && var->space == 1)
	{
		var->pad = ' ';
		return ;
	}
	if (var->prec == -1 && var->pad != '0')
		return ;
	if ((var->spec_width == 0 && var->pad != '0' && var->hash == 0))
		return ;
	if (var->hash == 1 && var->prec < 1 && var->spec_width == 0 \
		&& var->specifier != 'o')
		return ;
	var->print_zero = 1;
}

void	print_zero(t_print *var)
{
	is_zero(var);
	if (var->left == 1 && var->print_zero == 1)
		var->width += write(1, "0", 1);
	if (var->filled == 0 && var->space == 0)
		fill_width_int(var, 0 + var->print_zero + var->sign + \
			var->space, var->pad);
	else if (var->print_zero == 1 && var->space == 1 && var->spec_width > 0 \
		&& var->prec == -2 && var->pad == '0')
		fill_width_int(var, 2, '0');
	else if (var->filled == 0 && var->space == 1)
		fill_width_int(var, 0 + var->print_zero + var->sign + var->space, ' ');
	if (var->left == 0 && var->print_zero == 1)
		var->width += write(1, "0", 1);
}

void	do_integer(t_print *var, int base)
{
	get_int_arg(var, base);
	if (var->prec > 0)
	{
		var->zeros = var->prec - ft_strlen(var->print) + (var->ll_d < 0);
		var->pad = ' ';
		if (var->zeros < 0)
			var->zeros = 0;
	}
	if (var->ll_d < 0)
		var->plus = 0;
	if (var->plus == 1 || var->ll_d < 0)
		plusflag_or_negative(var);
	if (var->zeros < 0)
		var->zeros = 0;
	if (var->prec < 1 && var->ll_d == 0)
	{
		print_zero(var);
		ft_bzero(var->print, ft_strlen(var->print));
		free(var->print);
		return ;
	}
	print_integer(var, var->print);
}
