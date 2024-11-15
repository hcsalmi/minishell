/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:34:04 by esirnio           #+#    #+#             */
/*   Updated: 2021/12/15 16:39:11 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	char		*tempdest;
	const char	*tempsrc;

	tempdest = dest;
	tempsrc = src;
	while (n > 0 && *tempsrc != '\0')
	{
		*tempdest++ = *tempsrc++;
		n--;
	}
	while (n > 0)
	{
		*tempdest = '\0';
		tempdest++;
		n--;
	}
	return (dest);
}
