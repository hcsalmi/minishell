/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:14:45 by esirnio           #+#    #+#             */
/*   Updated: 2023/10/06 16:28:46 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_env(char *env, char *current)
{
	int	key_len;

	key_len = strchr_idx(current, '=');
	if (key_len == (int)ft_strlen(env))
	{
		if (ft_strncmp(current, env, key_len) == 0)
			return (1);
	}
	if (env[0] == '?')
		return (1);
	return (-1);
}

int	loop_current_list(char *env, t_data *data)
{
	int	cur;

	cur = 0;
	while (data->envs[cur])
	{
		if (find_env(env, data->envs[cur]) == 1)
			return (cur);
		cur++;
	}
	return (-1);
}

void	env_to_del_error(char *command, t_data *data)
{
	if (loop_current_list(command, data) != -1)
	{
		data->exit_status = 0;
		return ;
	}
	write(2, "StayFreshCheeseBags: ", 21);
	print_env_error(command, "unset", data);
	write(2, ": not a valid identifier\n", 25);
	data->exit_status = 1;
}

int	*are_they_in_envs(char **envs, t_data *data)
{
	int	*locations;
	int	i;
	int	loc_idx;

	i = 1;
	while (envs[i])
	{
		if (loop_current_list(envs[i], data) == -1)
			env_to_del_error(envs[i], data);
		i++;
	}
	locations = (int *)malloc(sizeof(int) * ft_array_size(envs));
	if (!locations)
		malloc_error();
	i = 1;
	loc_idx = 0;
	while (envs[i])
	{
		locations[loc_idx] = loop_current_list(envs[i], data);
		i++;
		loc_idx++;
	}
	return (locations);
}

void	del_envs(char **envs_to_del, t_data *data)
{
	int		*locations;
	char	**new_arr;

	data->exit_status = 0;
	if (envs_to_del[1] == NULL)
		return ;
	locations = are_they_in_envs(envs_to_del, data);
	if (locations == NULL)
	{
		data->exit_status = 1;
		return ;
	}
	new_arr = create_new_envs(locations, data);
	ft_free_2d_array((void **)data->envs, count_envs(data->envs));
	data->envs = new_arr;
	free (locations);
}
