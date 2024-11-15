/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:03:00 by esirnio           #+#    #+#             */
/*   Updated: 2023/10/05 21:22:08 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_bzero(arr[i], ft_strlen(arr[i]));
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}
