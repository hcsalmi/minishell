/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:18:47 by esirnio           #+#    #+#             */
/*   Updated: 2021/12/15 17:22:01 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *comp, size_t n)
{
	char	*temp;
	char	*temp2;

	if (ft_strlen(comp) == 0 || comp == haystack)
		return ((char *)haystack);
	while (n > 0 && *haystack != '\0')
	{
		if (*(char *)haystack == *(char *)comp && (ft_strlen(comp) <= n))
		{
			temp = (char *)haystack;
			temp2 = (char *)comp;
			while (*haystack == *comp && *comp != '\0')
			{
				haystack++;
				comp++;
			}
			if (*comp == '\0')
				return (temp);
			haystack = temp;
			comp = temp2;
		}
		haystack++;
		n--;
	}
	return (0);
}
