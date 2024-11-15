/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_envs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 16:50:54 by esirnio           #+#    #+#             */
/*   Updated: 2023/10/06 16:27:42 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_existing_env(char **current_envs, char *new)
{
	int		i;
	int		idx_equal_new;

	i = 0;
	idx_equal_new = strchr_idx(new, '=');
	while (current_envs[i])
	{
		if (ft_strncmp(current_envs[i], new, idx_equal_new) == 0)
		{
			free(current_envs[i]);
			current_envs[i] = ft_strdup(new);
			if (!current_envs[i])
				malloc_error();
			return (1);
		}
		i++;
	}
	return (0);
}

int	add_env_or_not(char *new_env, t_data *data)
{
	if (ft_isalnum(new_env[0]) != 1 && new_env[0] != '_')
	{
		env_to_add_error(new_env, data);
		return (0);
	}
	if (ft_strchr(new_env, '=') == 0
		|| replace_existing_env(data->envs, new_env) == 1)
	{
		return (0);
	}
	return (1);
}

char	**create_new_env_list(char *new_env, char **current_envs, int len)
{
	int		i;
	char	**new;

	i = 0;
	new = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new)
		malloc_error();
	while (i < len)
	{
		new[i] = ft_strdup(current_envs[i]);
		if (!new[i])
			malloc_error();
		i++;
	}
	new[i] = ft_strdup(new_env);
	if (!new[i])
		malloc_error();
	i++;
	new[i] = NULL;
	return (new);
}

void	add_envs(char **new_env, t_data *data)
{
	int		len;
	char	**new;
	int		j;

	data->exit_status = 0;
	j = 1;
	while (new_env[j])
	{
		if (add_env_or_not(new_env[j], data) == 0)
		{
			j++;
			continue ;
		}
		len = count_envs(data->envs);
		new = create_new_env_list(new_env[j], data->envs, len);
		ft_free_array(data->envs);
		data->envs = new;
	}
}
