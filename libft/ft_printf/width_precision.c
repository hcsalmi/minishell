/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:56:14 by esirnio           #+#    #+#             */
/*   Updated: 2023/07/06 17:09:42 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	check_width(t_print *var)
{
	int		len;
	char	*num_str;

	if (!(ft_isdigit(var->s[var->ind])))
		return ;
	len = 0;
	while (ft_isdigit(var->s[var->ind]))
	{
		len++;
		var->ind++;
	}
	var->ind = var->ind - len;
	num_str = ft_strnew(len);
	ft_strncpy(num_str, &var->s[var->ind], len);
	if (!num_str)
		exit (-1);
	var->spec_width = ft_atoi(num_str);
	var->ind += len;
	ft_bzero(num_str, ft_strlen(num_str));
	free(num_str);
}

void	length_modifier(t_print *var)
{
	if (var->s[var->ind] == 'l' && var->s[var->ind + 1] == 'l')
	{
		var->ind += 2;
		var->ll = 1;
	}
	else if (var->s[var->ind] == 'l')
	{
		var->ind++;
		var->l = 1;
	}
	if (var->s[var->ind] == 'h' && var->s[var->ind + 1] == 'h')
	{
		var->ind += 2;
		var->hh = 1;
	}
	else if (var->s[var->ind] == 'h')
	{
		var->ind++;
		var->h = 1;
	}
	if (var->s[var->ind] == 'L')
	{
		var->upper_l = 1;
		var->ind++;
	}
}

void	check_precision(t_print *var)
{
	var->ind++;
	if (!ft_isdigit(var->s[var->ind]))
		return ;
	while (ft_isdigit(var->s[var->ind]))
	{
		var->prec = 10 * var->prec + var->s[var->ind] - '0';
		var->ind++;
	}
	if (var->prec < -2)
		var->prec = 101;
}

void	check_width_and_precision(t_print *var)
{
	check_width(var);
	if (var->s[var->ind] == '.')
	{
		check_precision(var);
		if (var->prec == 0)
			var->prec = -1;
	}
	else
		var->prec = -2;
	length_modifier(var);
}

void	check_flags(t_print *var)
{
	while (1)
	{
		if (var->s[var->ind] == '-')
			var->left = 1;
		else if (var->s[var->ind] == '+')
			var->plus = 1;
		else if (var->s[var->ind] == ' ')
			var->space = 1;
		else if (var->s[var->ind] == '#')
			var->hash = 1;
		else if (var->s[var->ind] == '0' && var->s[var->ind + 1] != '.' )
			var->pad = '0';
		else
		{
			if (var->plus == 1)
				var->space = 0;
			if (var->left == 1)
				var->pad = ' ';
			break ;
		}
		var->ind++;
	}
}
