/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:47:28 by esirnio           #+#    #+#             */
/*   Updated: 2023/07/06 17:10:37 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	bigger_width_hexa(t_print *var, char *string)
{
	if (var->space == 1)
		var->width += write (1, " ", 1);
	if (var->left == 1)
	{
		if (var->prec != -1)
			hash_and_zeros(var);
		ft_putnstr(string, var->printlen - var->zeros, var);
	}
	if (var->sign == 0 || var->left == 1)
	{
		var->helper = var->printlen + var->space + var->hash + var->sign;
		if (var->pad == '0' && var->prec == -2)
			fill_width(var, var->helper, '0');
		else
			fill_width(var, var->helper, ' ');
	}
	if (var->left == 0)
	{
		if (var->prec != -1)
			hash_and_zeros(var);
		if (var->zeros > 0)
			var->printlen = var->printlen - var->zeros + var->sign;
		ft_putnstr(string, var->printlen, var);
	}
}

void	print_hexa(t_print *var, char *string)
{
	int	l;

	l = ft_strlen(string);
	if (var->unsigned_arg == 0)
		var->hash = 0;
	if (var->printlen == 0)
		var->printlen = ((l > var->prec) * l + !(l > var->prec) * var->prec);
	else if (l < var->printlen)
		var->printlen = l;
	if (var->printlen >= var->spec_width)
	{
		if (var->space == 1 && var->specifier != 'u')
			var->width += write(1, " ", 1);
		var->left = 1;
		if (var->prec != -1)
			hash_and_zeros(var);
		ft_putnstr(string, var->printlen - var->zeros, var);
	}
	else
		bigger_width_hexa(var, string);
}

void	hexa_zero(t_print *var)
{
	if (var->prec == -1)
		return ;
	if ((var->spec_width == 0 && var->pad != '0' && var->hash == 0))
		return ;
	if (var->hash == 1 && var->prec < 1 && var->pad == ' ' \
		&& var->spec_width == 0 && var->specifier != 'o')
		return ;
	var->print_zero = 1;
}

void	do_hexa(t_print	*var, int base)
{
	if (var->s[var->ind] == 'X')
		var->cap = 16;
	get_unsigned_arg(var, base);
	if (var->hash == 1)
		var->hash = 2;
	if (var->prec < 1 && var->unsigned_arg == 0)
	{
		hexa_zero(var);
		if (var->left == 1 && var->print_zero == 1)
			var->width += write(1, "0", 1);
		if (var->pad == '0' && var->prec != -1)
			fill_width(var, 0 + var->print_zero, '0');
		else
			fill_width(var, 0 + var->print_zero, ' ');
		if (var->left == 0 && var->print_zero == 1)
			var->width += write(1, "0", 1);
		return ;
	}
	if (var->prec > 0)
		var->zeros = var->prec - ft_strlen(var->print);
	if (var->zeros < 0)
		var->zeros = 0;
	print_hexa(var, var->print);
}
