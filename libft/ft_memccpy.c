/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 12:59:00 by esirnio           #+#    #+#             */
/*   Updated: 2021/12/12 16:26:01 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		stopc;
	const unsigned char	*newsrc;
	unsigned char		*newdst;

	i = 0;
	stopc = c;
	newsrc = src;
	newdst = dest;
	while (i < n)
	{
		newdst[i] = newsrc[i];
		if (newsrc[i] == stopc)
		{
			return ((void *) &newdst[i + 1]);
		}
		i++;
	}
	return (NULL);
}

/*void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		if (((unsigned char *)dest)[i] == (unsigned char)c)
			return (&dest[i + 1]);
		i++;
	}
	return (0);
}
*/