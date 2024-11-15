/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:42:55 by esirnio           #+#    #+#             */
/*   Updated: 2021/12/08 13:02:53 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	i;
	int		last;
	size_t	len;

	last = -1;
	i = 0;
	len = ft_strlen(str);
	while (i <= len)
	{
		if (((unsigned char *)str)[i] == (unsigned char)c)
			last = i;
		i++;
	}
	if (last == -1)
		return (0);
	return ((char *)&str[last]);
}
