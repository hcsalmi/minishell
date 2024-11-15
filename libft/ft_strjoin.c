/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:59:32 by esirnio           #+#    #+#             */
/*   Updated: 2021/12/17 16:39:01 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*con;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	j = -1;
	i = -1;
	len = ft_strlen(s1) + ft_strlen(s2);
	con = (char *)malloc(sizeof(char) * (len + 1));
	if (!con)
		return (NULL);
	while (s1[++i] != '\0')
		con[i] = s1[i];
	while (s2[++j] != '\0')
		con[i + j] = s2[j];
	con[i + j] = '\0';
	return (con);
}
