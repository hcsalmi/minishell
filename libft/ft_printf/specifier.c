/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:56:33 by esirnio           #+#    #+#             */
/*   Updated: 2023/09/07 16:13:41 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	check_specifier(t_print *var)
{
	var->specifier = var->s[var->ind];
	if (var->specifier == 'f')
		do_float(var);
	else if (var->specifier == 'd' || var->specifier == 'i')
		do_integer(var, 10);
	else if (var->specifier == 'c')
		do_char(var);
	else if (var->specifier == 's')
		do_string(var);
	else if (var->specifier == 'p')
		do_unsigned(var, 16);
	else if (var->specifier == 'x' || var->specifier == 'X')
		do_hexa(var, 16);
	else if (var->specifier == 'o')
		do_unsigned(var, 8);
	else if (var->specifier == 'u')
		do_unsigned(var, 10);
	else if (var->specifier == '%')
		do_modulo(var);
	else
		return (-1);
	if (var->specifier != 's' && var->specifier != 'f' && var->specifier != '%')
		ft_bzero(var->print, ft_strlen(var->print));
	return (1);
}

/* if specifier is %*/

void	do_modulo(t_print *var)
{
	if (var->left == 1)
		var->pad = ' ';
	if (var->left == 1)
		var->width += write(1, "%", 1);
	fill_width(var, 1, var->pad);
	if (var->left == 0)
		var->width += write(1, "%", 1);
}

void	print_str(t_print *var, char *str)
{
	if (var->prec > 0)
		var->printlen = var->prec;
	if (var->space == 1)
		var->width += write(1, str, ft_strlen(str));
	else if (var->prec != -1)
		print_conversion(var, str);
	else if (ft_strcmp(ft_strchr(str, '\0'), str))
		fill_width(var, 0, ' ');
	else if (var->prec == -1 && var->spec_width > (int)ft_strlen(str))
		print_conversion(var, str);
}

void	do_string(t_print *var)
{
	char	*str;

	str = ft_strdup(va_arg(var->args, char *));
	if (str == NULL)
	{
		str = ft_strdup("(null)");
		print_str(var, str);
	}
	else if (str[0] == '\0' && var->spec_width < 1)
	{
		free(str);
		return ;
	}
	else if (str[0] == '\0' && var->spec_width > 0)
	{
		while (var->spec_width-- > 0)
			var->width += write(1, " ", 1);
	}
	else
		print_str(var, str);
	free(str);
}
