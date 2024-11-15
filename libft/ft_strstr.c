/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:43:51 by esirnio           #+#    #+#             */
/*   Updated: 2021/12/08 13:10:15 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *comp)
{
	char	*temp;
	char	*temp2;

	if (comp[0] == '\0' || str == comp)
		return ((char *)str);
	temp2 = (char *)comp;
	while (*str)
	{
		if (*str == *temp2)
		{
			temp = (char *)str;
			while (*temp2 != '\0')
			{
				if (*temp2 != *temp++)
					break ;
				temp2++;
			}
			if (*temp2 == '\0')
				return ((char *)str);
		}
		temp2 = (char *)comp;
		str++;
	}
	str = (0);
	return ((char *)str);
}
