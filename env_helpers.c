/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalmi <lsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:14:32 by lsalmi            #+#    #+#             */
/*   Updated: 2023/10/06 16:32:52 by lsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_envs(char **envs)
{
	int	i;

	i = 0;
	while (envs[i])
		i++;
	return (i);
}

void	replace_env(char **current, int idx, char *replace)
{
	char	*new;

	new = (char *)malloc(sizeof(char) * (idx + ft_strlen(replace) + 1));
	if (!new)
		malloc_error();
	new = shell_strjoin(new, replace);
	if (!new)
		malloc_error();
	free(*current);
	*current = new;
}

char	*ft_get_env_value(char **current_envs, char *key)
{
	int		i;
	int		idx_equal;

	i = 0;
	while (current_envs[i])
	{
		idx_equal = strchr_idx(current_envs[i], '=');
		if (ft_strncmp(current_envs[i], key, idx_equal) == 0)
			return (ft_strdup(current_envs[i] + idx_equal + 1));
		i++;
	}
	return (NULL);
}

int	is_to_be_removed(int cur, int *delete_idxs)
{
	int	i;

	i = 0;
	while (delete_idxs[i])
	{
		if (delete_idxs[i] == cur)
			return (1);
		i++;
	}
	return (0);
}

char	**create_new_envs(int *locations, t_data *data)
{
	int		len;
	char	**new;
	int		i;
	int		j;

	len = count_envs(data->envs);
	new = (char **)malloc(sizeof(char *) * len);
	if (!new)
		malloc_error();
	i = -1;
	j = 0;
	while (data->envs[++i])
	{
		if (is_to_be_removed(i, locations) == 1)
			continue ;
		new[j] = ft_strdup(data->envs[i]);
		if (!new[j])
			malloc_error();
		j++;
	}
	new[j] = NULL;
	return (new);
}
