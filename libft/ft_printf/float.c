/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:30:20 by esirnio           #+#    #+#             */
/*   Updated: 2023/07/06 17:10:47 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	get_rounded(t_print *var)
{
	long double	rounder;
	int			i;

	rounder = 1;
	i = 0;
	while (i < var->prec)
	{
		rounder /= 10;
		i++;
	}
	var->float_arg += rounder;
}

void	check_decimals(t_print *var)
{
	long double	d;
	int			i;
	long double	temp;

	d = var->float_arg - (long long)var->float_arg;
	i = 0;
	if (var->prec == -1)
	{
		if (d > 0.5)
			get_rounded(var);
		if (d == 0.5)
			if ((long long)var->float_arg % 2 != 0)
				get_rounded(var);
		return ;
	}
	while (i++ < var->prec)
		d = d * 10;
	temp = d - (long long)d;
	if (temp > 0.5)
		get_rounded(var);
	if (temp == 5.0)
		if ((long long)d % 2 != 0)
			get_rounded(var);
}

void	float_plus_minus(t_print *var)
{
	int	len;

	if (var->minus == 1)
	{
		var->float_arg *= -1.0;
		len = ft_intlen((long long)var->float_arg) + 1;
		if (var->prec > 0)
			len += var->prec;
		if (var->prec != -1 || (var->prec == -1 && var->hash == 1))
			len += 1;
		if (var->pad == ' ' && var->left == 0)
			fill_width_float(var, len, ' ');
		var->width += write(1, "-", 1);
	}
	else if (var->plus == 1)
		var->width += write(1, "+", 1);
	var->plus = 0;
	var->space = 0;
	var->sign = 1;
}

void	get_float_arg(t_print *var)
{
	if (var->upper_l == 1)
		var->float_arg = (long double)va_arg(var->args, long double);
	else
		var->float_arg = (double)va_arg(var->args, double);
	if (var->float_arg == -0.0 && 1 / var->float_arg < 0.0)
		var->minus = 1;
	if (var->float_arg < 0)
		var->minus = 1;
}

void	do_float(t_print *var)
{
	long long	value;

	if (var->prec == -2)
		var->prec = 6;
	get_float_arg(var);
	if (var->plus == 1 || var->minus == 1)
		float_plus_minus(var);
	check_decimals(var);
	value = (long long)var->float_arg;
	print_float(var, value);
}
