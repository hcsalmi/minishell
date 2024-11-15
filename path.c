/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:30:31 by esirnio           #+#    #+#             */
/*   Updated: 2023/10/06 18:19:53 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_working_path(char *str)
{
	int	fd;

	fd = open(str, O_DIRECTORY);
	if (access(str, X_OK | F_OK) == 0 && fd == -1)
		return (1);
	close(fd);
	return (0);
}

char	*create_path_to_try(char *path, char *command)
{
	char	*path_to_try;
	char	*temp;

	temp = NULL;
	path_to_try = NULL;
	temp = ft_strjoin(path, "/");
	if (!temp)
		malloc_error();
	path_to_try = ft_strjoin(temp, command);
	if (!path_to_try)
		malloc_error();
	free(temp);
	return (path_to_try);
}

char	*find_path(char **splitted_path, char *command)
{
	int		i;
	char	*path_to_try;

	i = 0;
	path_to_try = NULL;
	while (splitted_path && splitted_path[i])
	{
		path_to_try = create_path_to_try(splitted_path[i], command);
		if (access(path_to_try, F_OK | X_OK) == 0)
			return (path_to_try);
		if (path_to_try)
			free(path_to_try);
		i++;
	}
	return (NULL);
}

char	*set_path(char *command, t_data *data)
{
	char	*path;
	char	**splitted_path;
	char	*path_to_return;

	path = NULL;
	splitted_path = NULL;
	path_to_return = NULL;
	path = ft_get_env_value(data->envs, "PATH=");
	if (path == NULL)
	{
		if (!check_if_working_path(command))
			return (NULL);
		else
			return (command);
	}
	if (path)
	{
		splitted_path = ft_strsplit(path, ':');
		free(path);
		if (!splitted_path)
			malloc_error();
	}
	path_to_return = find_path(splitted_path, command);
	ft_free_array(splitted_path);
	return (path_to_return);
}
