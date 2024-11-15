/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:51:47 by esirnio           #+#    #+#             */
/*   Updated: 2023/09/07 16:13:17 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	hexa_prefix(t_print *var)
{
	if (var->hash == 0)
		return ;
	if (var->prec == -1 && var->unsigned_arg == 0)
		var->printlen = 0;
	if (var->unsigned_arg == 0)
	{
		var->hash = 0;
		return ;
	}
	if (var->specifier == 'x')
		ft_putstr("0x");
	else if (var->specifier == 'X')
		ft_putstr("0X");
	var->width += 2;
}

void	fill_before_sign_int(t_print *var, int len)
{
	if (var->left == 0 && var->spec_width > 0 && var->pad == ' ')
		fill_width_int(var, len, var->pad);
	if (var->left == 0 && var->spec_width > 0 && var->prec == 0)
		fill_width_int(var, len, ' ');
	if (var->ll_d == 0 && var->left == 0 && var->pad != '0' && var->prec == 0)
		var->width += write(1, " ", 1);
	if (var->ll_d == 0 && var->pad == '0' && var->left == 0 && var->prec == -1)
		fill_width_int(var, 1, ' ');
	if (var->pad == '0' && var->prec == -1 && len < var->spec_width && \
		var->left == 0)
		fill_width_int(var, len, ' ');
}

void	hash(t_print	*var)
{
	if (var->specifier == 'f')
		var->hash = 0;
	if (ft_strchr("xXop", var->specifier) == 0)
		return ;
	if (var->specifier != 'p' && var->hash == 0)
		return ;
	if ((var->specifier == 'x' || var->specifier == 'X'))
		hexa_prefix(var);
	else if (var->specifier == 'p')
	{
		ft_putstr("0x");
		var->width += 2;
	}
	else if (var->hash == 1)
	{
		var->zeros--;
		if (var->print[0] == '0' && var->printlen == 1)
		{
			var->hash = 0;
			return ;
		}
		var->width += write(1, "0", 1);
	}
}

void	hash_and_zeros(t_print *var)
{
	int	i;

	i = 0;
	hash(var);
	if (var->left == 0)
	{
		while (i++ < var->zeros - var->sign)
			var->width += write (1, "0", 1);
	}
	else
		while (i++ < var->zeros)
			var->width += write (1, "0", 1);
	if (var->zeros < 0)
		var->zeros = 0;
}
