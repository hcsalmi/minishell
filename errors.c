/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalmi <lsalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:24:02 by lsalmi            #+#    #+#             */
/*   Updated: 2023/10/06 21:24:03 by lsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error_near_token(t_data *data)
{
	write(2, "StayFreshCheeseBags: ", 21);
	write(2, "syntax error near unexpected token\n", 35);
	data->exit_status = 258;
}

void	exit_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(112);
}

void	open_error(t_data *data)
{
	write(2, "StayFreshCheeseBags: open error\n", 32);
	data->exit_status = 1;
}

void	print_env_error(char *command, char *action, t_data *data)
{
	write(2, action, ft_strlen(action));
	write(2, " '", 2);
	write(2, command, ft_strlen(command));
	write(2, "'", 2);
	data->exit_status = 1;
}

void	env_to_add_error(char *command, t_data *data)
{
	write(2, "StayFreshCheeseBags: ", 21);
	print_env_error(command, "export", data);
	write(2, ": not a valid identifier\n", 25);
	data->exit_status = 1;
}
