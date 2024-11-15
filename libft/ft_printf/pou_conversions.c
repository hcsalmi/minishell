/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pou_conversions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:56:23 by esirnio           #+#    #+#             */
/*   Updated: 2023/07/06 17:10:29 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_itoa_uns(unsigned long long value, int base, int capital)
{
	static char	hex[] = "0123456789abcdef0123456789ABCDEF";
	static char	buf[50];
	char		*ret;
	int			i;

	ret = &buf[49];
	*ret = '\0';
	i = 1;
	while (1)
	{
		ret--;
		*ret = hex[(value % base) + capital];
		value = value / base;
		if (value == 0)
			break ;
	}
	if (i == -1)
		*--ret = '-';
	return (ret);
}

void	get_unsigned_arg(t_print *var, int base)
{
	if (var->ll == 1 || var->specifier == 'p')
		var->unsigned_arg = va_arg(var->args, unsigned long long);
	else if (var->l == 1)
		var->unsigned_arg = va_arg(var->args, unsigned long);
	else if (var->hh == 1)
		var->unsigned_arg = (unsigned char)va_arg(var->args, unsigned int);
	else if (var->h == 1)
		var->unsigned_arg = (unsigned short)va_arg(var->args, unsigned int);
	else
		var->unsigned_arg = (unsigned long long)va_arg(var->args, unsigned int);
	var->print = ft_itoa_uns((long long)var->unsigned_arg, base, var->cap);
}

/*checks if zero value needs to be printed*/

void	unsigned_zero(t_print *var)
{
	if (var->prec == -1 && var->hash == 0)
		return ;
	if (var->prec == -1 && ft_strchr("xX", var->specifier) != 0)
		return ;
	if ((var->prec == -1 && var->pad != '0' && var->hash == 0 && \
		(var->specifier != 'o')))
		return ;
	if ((var->spec_width == 0 && var->pad != '0' && var->hash == 0))
		return ;
	if (var->hash == 1 && var->prec < 1 && var->pad == ' ' \
		&& var->spec_width == 0 && var->specifier != 'o')
		return ;
	var->print_zero = 1;
}

/*this prepares conversions p,o,u to print*/

void	do_unsigned(t_print	*var, int base)
{
	get_unsigned_arg(var, base);
	if (var->prec < 1 && var->unsigned_arg == 0 && var->specifier != 'p')
	{
		unsigned_zero(var);
		if (var->space == 1)
			var->width += write (1, " ", 1);
		if (var->left == 1 && var->print_zero == 1)
			var->width += write(1, "0", 1);
		if (var->prec > 0 && var->prec > var->spec_width)
			fill_width(var, var->spec_width - var->prec - 1, var->pad);
		else
			fill_width(var, 0 + var->print_zero, var->pad);
		if (var->left == 0 && var->print_zero == 1)
			var->width += write(1, "0", 1);
		return ;
	}
	if (var->prec > 0)
		var->zeros = var->prec - ft_strlen(var->print);
	if (var->zeros < 0)
		var->zeros = 0;
	print_conversion(var, var->print);
}
