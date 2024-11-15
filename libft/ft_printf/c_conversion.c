/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_conversion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 19:52:55 by esirnio           #+#    #+#             */
/*   Updated: 2023/07/06 17:10:51 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	do_char(t_print *var)
{
	int	ch;

	ch = va_arg(var->args, int);
	var->printlen = 1;
	if (var->spec_width > 0)
		var->printlen = var->spec_width;
	var->print = (char *)malloc(sizeof(char) * var->printlen);
	if (!var->print)
		exit (-1);
	var->print[var->printlen] = '\0';
	add_to_print(var, ch);
	if (var->left == 1)
		move_left(var);
	var->width += write(1, var->print, var->printlen);
	free(var->print);
}

void	add_to_print(t_print *var, int ch)
{
	int	i;
	int	len;

	i = 0;
	len = var->printlen;
	while (len - 1 > 0)
	{
		if (var->pad == '0')
			var->print[i] = '0';
		else
			var->print[i] = ' ';
		len--;
		i++;
	}
	var->print[i] = ch;
}

void	move_left(t_print *var)
{
	int	i;
	int	len;

	i = 0;
	len = var->printlen;
	while (len > 0)
	{
		while (var->print[i] == ' ')
			i++;
		if (i == 0)
			return ;
		while (i < len)
		{
			var->print[i - 1] = var->print[i];
			var->print[i] = ' ';
			i++;
		}
		i = 0;
		len--;
	}
}
