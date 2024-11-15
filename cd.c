/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:55:25 by esirnio           #+#    #+#             */
/*   Updated: 2023/10/06 19:23:36 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_path(char *replace, char **envs, char *to_replace, t_data *data)
{
	int		i;
	int		idx_equal;

	i = 0;
	while (envs[i])
	{
		idx_equal = strchr_idx(envs[i], '=');
		if (ft_strncmp(envs[i], to_replace, idx_equal) == 0)
		{
			idx_equal++;
			replace_env(&data->envs[i], idx_equal, replace);
		}
		i++;
	}
}

int	update_old_pwd(t_data *data)
{
	char	*pwd_old;

	pwd_old = NULL;
	pwd_old = get_path();
	if (!pwd_old)
	{
		write(2, "StayFreshCheeseBags: getcwd error\n", 34);
		data->exit_status = 1;
		return (-1);
	}
	update_path(pwd_old, data->envs, "OLDPWD=", data);
	free(pwd_old);
	return (1);
}

int	update_new_pwd(t_data *data)
{
	char	*pwd_new;

	pwd_new = NULL;
	pwd_new = get_path();
	if (!pwd_new)
	{
		write(2, "StayFreshCheeseBags: getcwd error\n", 34);
		data->exit_status = 1;
		return (-1);
	}
	update_path(pwd_new, data->envs, "PWD=", data);
	free(pwd_new);
	return (1);
}

int	go_home(t_data *data)
{
	char	*home_path;

	home_path = NULL;
	home_path = ft_get_env_value(data->envs, "HOME=");
	if (chdir(home_path) == -1)
	{
		write(2, "StayFreshCheeseBags: cd: HOME not set\n", 38);
		data->exit_status = 1;
		if (home_path)
			free(home_path);
		return (-1);
	}
	if (home_path)
		free(home_path);
	return (1);
}

void	do_cd(char **command, t_data *data)
{
	if (update_old_pwd(data) == -1)
		return ;
	if (command[1])
	{
		if (chdir(command[1]) == -1)
		{
			not_a_directory_error(command[1], data);
			return ;
		}
	}
	else
	{
		if (go_home(data) == -1)
			return ;
	}
	if (update_new_pwd(data) == -1)
		return ;
	data->exit_status = 0;
}
