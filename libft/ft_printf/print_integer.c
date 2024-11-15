/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_integer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:02:35 by esirnio           #+#    #+#             */
/*   Updated: 2023/07/06 17:10:14 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	fill_width_int(t_print *var, int num, char pad)
{
	if (var->ll_d == 0 && var->sign == 1 && var->left == 0 && \
		var->prec == -2 && var->pad == ' ')
		return ;
	while (num < var->spec_width)
	{
		var->width += write(1, &pad, 1);
		num++;
		var->filled = 1;
	}
}

void	check_fill(t_print	*var)
{
	if (var->space == 1 && var->pad == '0' && var->prec == -1)
		fill_width_int(var, var->helper, ' ');
	else if (var->sign == 0 || var->left == 1 || var->pad == '0')
		fill_width_int(var, var->helper, var->pad);
	else if (var->sign == 0 && var->prec != -1)
		fill_width_int(var, var->helper, ' ');
}

/* bigger_width fills width that is left after printlengt
	also checks if extra zeros or hash- flag needs to be printed*/

void	bigger_width_int(t_print *var, char *string)
{
	if (var->space == 1 || var->hash == 1)
		var->width += write (1, " ", 1);
	if (var->left == 1)
	{
		hash_and_zeros(var);
		ft_putnstr(string, var->printlen - var->zeros, var);
	}
	if (var->space == 1 && var->hash == 1)
		var->space = 0;
	var->helper = var->printlen + var->space + var->hash + var->sign;
	if (var->filled == 0)
		check_fill(var);
	if (var->left == 0)
	{
		hash_and_zeros(var);
		if (var->zeros > 0)
			var->printlen = var->printlen - var->zeros + var->sign;
		ft_putnstr(string, var->printlen, var);
	}
}

/*function above calculates length to print and prints it.
	if conversion width is bigger, goes to bigger_width_int function*/

void	print_integer(t_print *var, char *string)
{
	int	l;

	l = ft_strlen(string);
	if (var->minus == 1)
		l--;
	var->printlen = ((l > var->prec) * l + !(l > var->prec) * var->prec);
	if (var->printlen >= var->spec_width)
	{
		if (var->space == 1 || var->hash == 1)
			var->width += write(1, " ", 1);
		var->left = 1;
		hash_and_zeros(var);
		ft_putnstr(string, var->printlen - var->zeros, var);
	}
	else
		bigger_width_int(var, string);
	ft_bzero(string, ft_strlen(var->print));
	free(string);
}
