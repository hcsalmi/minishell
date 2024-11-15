/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:51:35 by esirnio           #+#    #+#             */
/*   Updated: 2023/07/06 17:10:44 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*checks flags, conversion width and precision. Then check specifier*/

int	check_conversion(t_print	*var)
{
	var->ind++;
	check_flags(var);
	check_width_and_precision(var);
	if (var->prec > 100 || var->spec_width > 200)
	{
		ft_putendl("> > > > > > Large values\n");
		exit(-1);
	}
	if (check_specifier(var) == -1)
	{
		ft_putendl("> > > > > > I do not know this one\n");
		exit(-1);
	}
	var->ind++;
	return (1);
}

/* prints fmt unless there is % sign. If % found, lets go to see conversion*/

int	ft_printf(const char	*fmt, ...)
{
	t_print	var;

	var.s = NULL;
	start_values(&var);
	va_start(var.args, fmt);
	var.s = (char *)fmt;
	while (var.s[var.ind] != '\0')
	{
		if (var.s[var.ind] == '%')
		{
			check_conversion(&var);
			set_values(&var);
			continue ;
		}
		var.width += write(1, &var.s[var.ind], 1);
		var.ind++;
	}
	va_end(var.args);
	return (var.width);
}
