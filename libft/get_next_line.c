/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 16:34:55 by esirnio           #+#    #+#             */
/*   Updated: 2023/06/12 12:36:00 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*add(char *line, char *s)
{
	char	*temp;

	if (!s || *s == '\0')
		return (line);
	if (line == 0)
	{
		temp = ft_memalloc(ft_strlen(s) + 1);
		if (!temp)
		{
			exit(EXIT_FAILURE);
		}
		ft_strcpy(temp, s);
	}
	else
	{
		temp = ft_strjoin(line, s);
		free(line);
	}
	line = temp;
	return (line);
}

static char	*make_line(char *line)
{
	size_t	size;
	char	*temp;

	size = 0;
	temp = line;
	while (*temp++ != '\n')
		size++;
	temp = ft_memalloc(size + 1);
	if (!temp)
		exit(EXIT_FAILURE);
	temp = ft_strncpy(temp, line, size);
	free(line);
	line = temp;
	return (line);
}

int	get_next_line(const int fd, char **line)
{
	static char	s[MAX_FD][BUFF_SIZE + 1];
	ssize_t		r;

	if (fd < 0 || fd > 4096 || line == NULL || (read(fd, s[fd], 0) == -1))
		return (-1);
	*line = 0;
	r = -1;
	while (1)
	{
		*line = add(*line, s[fd]);
		ft_bzero(s[fd], ft_strlen(s[fd]));
		if (line && *line && ft_strchr(*line, '\n'))
		{
			ft_strncpy(s[fd], (ft_strchr(*line, '\n') + 1), BUFF_SIZE);
			*line = make_line(*line);
			return (1);
		}
		r = read(fd, s[fd], BUFF_SIZE);
		if (r == -1)
			return (-1);
		if (r == 0 && *line == 0)
			return (0);
		if (r == 0 && *line)
			return (1);
	}
}
