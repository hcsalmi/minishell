/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 15:09:42 by lsalmi            #+#    #+#             */
/*   Updated: 2023/09/25 21:16:11 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strchr_idx(char *str, char delimiter)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == delimiter)
			return (i);
		i++;
		str++;
	}
	return (-1);
}

void	ft_free_2d_array(void **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*ft_strndup(const char *src, size_t len)
{
	char	*temp;
	int		i;

	i = 0;
	temp = (char *)malloc(sizeof(char) * len + 1);
	if (temp == NULL)
		return (0);
	while (len > 0)
	{
		temp[i] = src[i];
		i++;
		len--;
	}
	temp[i] = '\0';
	return (temp);
}
