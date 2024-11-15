/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:18:32 by esirnio           #+#    #+#             */
/*   Updated: 2023/10/06 16:38:23 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_str_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			i++;
		else
			return (0);
	}
	return (1);
}

void	do_exit(char **command, t_data *data)
{
	write(1, "exit\n", 5);
	if (!command[1] || command[1][0] == '\0')
		exit(data->exit_status);
	if (command[1] && command[2])
	{
		write(2, "StayFreshCheeseBags: exit: too many arguments\n", 46);
		exit(255);
	}
	else if (command[1] && is_str_number(command[1]) == 0)
	{
		write(2, "StayFreshCheeseBags: exit: ", 27);
		write(2, command[1], ft_strlen(command[1]));
		write(2, ": numeric argument required\n", 28);
		exit (255);
	}
	else if (command[1])
		exit (ft_atoi(command[1]));
	else
		exit (data->exit_status);
}

int	is_builtin(char *str)
{
	if (str == NULL)
		return (-1);
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(str, "export") == 0)
		return (1);
	else if (ft_strcmp(str, "unset") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (-1);
}

void	display_export_list(char **envs)
{
	int	i;
	int	value_start;
	int	key_end;

	i = 0;
	while (envs[i])
	{
		write(1, "declare -x ", 11);
		key_end = strchr_idx(envs[i], '=');
		value_start = strchr_idx(envs[i], '=') + 1;
		write(1, envs[i], key_end + 1);
		write(1, "\"", 1);
		write(1, envs[i] + value_start, ft_strlen(envs[i] + value_start));
		write(1, "\"", 1);
		write(1, "\n", 1);
		i++;
	}
}

int	do_builtin(t_node *head, t_data *data)
{
	int	i;

	i = 0;
	if (ft_strcmp(head->command[i], "echo") == 0)
		do_echo(head, data);
	else if (ft_strcmp(head->command[i], "cd") == 0)
		do_cd(head->command, data);
	else if (ft_strcmp(head->command[i], "pwd") == 0)
		do_pwd(data);
	else if (ft_strcmp(head->command[i], "export") == 0)
	{
		if (head->command[i + 1] == NULL)
			display_export_list(data->envs);
		else
			add_envs(head->command, data);
	}
	else if (ft_strcmp(head->command[i], "unset") == 0)
		del_envs(head->command, data);
	else if (ft_strcmp(head->command[i], "env") == 0)
		print_envs(data->envs);
	else if (ft_strcmp(head->command[i], "exit") == 0)
		do_exit(head->command, data);
	return (0);
}
