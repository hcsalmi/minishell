/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:14:45 by esirnio           #+#    #+#             */
/*   Updated: 2021/12/15 17:20:55 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	lendest;
	size_t	i;
	size_t	r;

	lendest = ft_strlen(dest);
	if (size > lendest)
		r = ft_strlen(src) + lendest;
	else
		r = ft_strlen(src) + size;
	i = 0;
	if (size > 0 && lendest < size - 1)
	{
		while (src[i] && lendest < size - 1)
		{
			dest[lendest] = src[i];
			i++;
			lendest++;
		}
		dest[lendest] = '\0';
	}
	return (r);
}
