/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:12:19 by esirnio           #+#    #+#             */
/*   Updated: 2021/11/15 18:22:24 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*temp;
	const char	*temp2;

	if (!dest && !src)
		return (dest);
	temp = dest;
	temp2 = src;
	while (n > 0)
	{
		*temp++ = *temp2++;
		n--;
	}
	return (dest);
}
