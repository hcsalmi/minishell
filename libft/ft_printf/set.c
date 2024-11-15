/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:56:40 by esirnio           #+#    #+#             */
/*   Updated: 2023/07/06 17:10:05 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	start_values(t_print *var)
{
	var->width = 0;
	var->ind = 0;
	set_values(var);
}

void	set_values(t_print *var)
{
	var->unsigned_arg = 0;
	var->minus = 0;
	var->specifier = 'a';
	var->spec_width = -1;
	var->print_zero = 0;
	var->float_arg = 0;
	var->rounding = 0;
	var->printlen = 0;
	var->upper_l = 0;
	var->helper = 0;
	var->filled = 0;
	var->zeros = 0;
	var->pad = ' ';
	var->space = 0;
	var->left = 0;
	var->plus = 0;
	var->prec = 0;
	var->ll_d = 0;
	var->hash = 0;
	var->sign = 0;
	var->cap = 0;
	var->hh = 0;
	var->ll = 0;
	var->h = 0;
	var->l = 0;
}
