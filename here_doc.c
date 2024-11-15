/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:57:59 by esirnio           #+#    #+#             */
/*   Updated: 2023/10/06 15:45:29 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_here_doc_files(t_data *data)
{
	int		i;
	char	*filename;

	i = 1;
	while (i <= data->heredoc_count)
	{
		filename = ft_strjoin("heredoc", ft_itoa(i));
		if (!filename)
			malloc_error();
		unlink(filename);
		free(filename);
		i++;
	}
	data->heredoc_count = 0;
}

char	*do_filename(int heredoc_number)
{
	char	*filename;
	char	*temp;

	temp = ft_itoa(heredoc_number);
	filename = ft_strjoin("heredoc", temp);
	if (!filename)
		malloc_error();
	free(temp);
	return (filename);
}

int	here_doc(char *delimiter, t_data *data)
{
	int		fd;
	char	*line;
	char	*file_name;

	file_name = do_filename(data->heredoc_count);
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
	{
		free(file_name);
		open_error(data);
	}
	while (1)
	{
		line = readline(">");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (line)
				free(line);
			free(file_name);
			break ;
		}
		ft_putstr_fd(line, fd);
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	fd = open(file_name, O_RDONLY);
	free(file_name);
	if (fd < 0)
		open_error(data);
	return (fd);
}
