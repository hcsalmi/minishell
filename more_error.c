/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalmi <lsalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:24:02 by lsalmi            #+#    #+#             */
/*   Updated: 2023/10/06 21:24:03 by lsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_error(t_node *node)
{
	ft_putstr_fd("StayFreshCheeseBags: ", 2);
	ft_putstr_fd(node->command[0], 2);
	if (node->command[0] != NULL && ft_strchr(node->command[0], '/') && \
	access(node->command[0], F_OK) == 0)
	{
		ft_putstr_fd(": is a directory\n", 2);
		exit(126);
	}
	else if (node->command[0] != NULL && \
	ft_strchr(node->command[0], '/') && access(node->command[0], F_OK) != 0)
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

void	malloc_error(void)
{
	write(2, "StayFreshCheeseBags: Memory allocation failed\n", 46);
	exit (666);
}

void	permission_error(char *command, t_data *data)
{
	write(2, "StayFreshCheeseBags: ", 21);
	write(2, command, ft_strlen(command));
	write(2, ": Permission denied\n", 20);
	data->exit_status = 126;
}

void	command_not_found(char *command, t_data *data)
{
	write(2, "StayFreshCheeseBags: ", 21);
	write(2, command, ft_strlen(command));
	write(2, ": command not found\n", 20);
	data->exit_status = 127;
}

void	not_a_directory_error(char *str, t_data *data)
{
	write(2, "StayFreshCheeseBags: ", 21);
	write(2, str, ft_strlen(str));
	write(2, ": Not a directory\n", 18);
	data->exit_status = 1;
}
