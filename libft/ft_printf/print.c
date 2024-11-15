/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:32:12 by esirnio           #+#    #+#             */
/*   Updated: 2023/07/06 17:10:10 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putnstr(char const *str, int n, t_print *var)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	if (var->minus == 1)
	{
		i++;
		n++;
	}
	while (i < n)
	{
		var->width += write(1, &str[i], 1);
		i++;
	}
}

void	fill_width(t_print *var, int num, char pad)
{
	if (var->sign == 1 && var->left == 0)
		return ;
	if (pad == '0' && (var->specifier == 'x' || var->specifier == 'X') \
		&& var->left == 0)
	{
		hash(var);
		var->hash = 0;
	}
	if (var->specifier == 'f' && var->hash == 1)
		num--;
	while (num < var->spec_width)
	{
		var->width += write(1, &pad, 1);
		num++;
		var->filled = 1;
	}
}

/* bigger_width fills width that is left after printlengt
	also checks if extra zeros or hash- flag needs to be printed*/
void	print_to_right(t_print *var, char *string)
{
	hash_and_zeros(var);
	if (var->zeros > 0)
		var->printlen = var->printlen - var->zeros + var->sign;
	ft_putnstr(string, var->printlen, var);
}

void	bigger_width(t_print *var, char *string)
{
	if (var->space == 1 && var->specifier != 'u')
		var->width += write (1, " ", 1);
	if (var->specifier == 'o' && var->zeros > 0)
		var->hash = 0;
	if (var->left == 1)
	{
		hash_and_zeros(var);
		ft_putnstr(string, var->printlen - var->zeros, var);
	}
	if (var->sign == 0 || var->left == 1)
	{
		var->helper = var->printlen + var->space + var->hash + var->sign;
		if (var->prec == -1 && var->pad == '0')
			fill_width(var, var->helper, ' ');
		else if (var->zeros == 0 && var->pad == '0' && var->prec < 1)
			fill_width(var, var->helper, '0');
		else
			fill_width(var, var->helper, ' ');
	}
	if (var->left == 0)
		print_to_right(var, string);
}

/*function above calculates length to print and prints it.
	if conversion width is bigger, goes to bigger_width function*/

void	print_conversion(t_print *var, char *string)
{
	int	l;

	l = ft_strlen(string);
	if (var->printlen == 0)
		var->printlen = ((l > var->prec) * l + !(l > var->prec) * var->prec);
	if (l < var->printlen && (var->specifier == 's' || var->specifier == 'c'))
		var->printlen = l;
	if (var->specifier == 'p')
		var->hash = 2;
	if (var->printlen >= var->spec_width)
	{
		if (var->space == 1 && var->specifier != 'u')
			var->width += write(1, " ", 1);
		var->left = 1;
		hash_and_zeros(var);
		if (var->specifier == 'p' && string[0] == '0' && var->prec == -1)
			return ;
		if (var->specifier == 'o' && var->prec > 0)
			var->printlen -= var->hash;
		ft_putnstr(string, var->printlen - var->zeros, var);
	}
	else
		bigger_width(var, string);
}
