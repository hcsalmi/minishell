/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:08:41 by esirnio           #+#    #+#             */
/*   Updated: 2023/07/06 17:10:17 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	print_value(t_print *var, long long value)
{
	int			i;
	long double	temp;
	int			print;

	i = 0;
	ft_putnbr(value);
	var->width += ft_intlen(value);
	if (var->prec != -1)
		var->width += write(1, ".", 1);
	else if (var->hash == 1)
		var->width += write(1, ".", 1);
	temp = var->float_arg - (long long)var->float_arg;
	while (i < var->prec)
	{
		print = temp * 10;
		temp *= 10.0;
		temp = temp - print;
		ft_putnbr(print);
		var->width++;
		i++;
	}
}

void	fill_width_float(t_print *var, int num, char pad)
{
	if (var->left == 1)
		pad = ' ';
	while (num < var->spec_width)
	{
		var->width += write(1, &pad, 1);
		num++;
		var->filled = 1;
	}
}

void	bigger_width_float(t_print *var, long long value)
{
	if (var->space == 1)
		var->width += write (1, " ", 1);
	if (var->left == 0 && var->pad == '0')
		fill_width_float(var, var->printlen + var->space, '0');
	else if (var->left == 0 && var->pad == ' ' && var->sign == 0)
		fill_width_float(var, var->printlen + var->space, ' ');
	if (var->left == 1)
		print_value(var, value);
	if (var->sign == 0 && var->left == 1)
		fill_width_float(var, var->printlen + var->space, '0');
	if (var->left == 1 && var->sign == 1 && var->filled == 0)
		fill_width_float(var, var->printlen + var->space, ' ');
	if (var->left == 0)
		print_value(var, value);
}

/* in print_float function printlen + 1 is for dot 
	so when possible extra width is filled, it leaves space for dot*/

void	print_float(t_print *var, long long value)
{
	var->printlen = ft_intlen(value) + var->sign;
	if (var->prec != -1 || (var->prec == -1 && var->hash == 1))
		var->printlen += 1;
	if (var->prec > 0)
		var->printlen += var->prec;
	if (var->printlen >= var->spec_width)
	{
		if (var->space == 1)
			var->width += write(1, " ", 1);
		var->left = 1;
		print_value(var, value);
	}
	else
		bigger_width_float(var, value);
}
