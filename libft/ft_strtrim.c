/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 12:46:52 by esirnio           #+#    #+#             */
/*   Updated: 2023/10/05 22:24:16 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

//gyhujkl

static int	ft_space(size_t c, char del)
{
	if (c == (size_t)del)
		return (1);
	return (0);
}

static int	check_len(size_t end, size_t start)
{
	int	len;

	len = end - start + 1;
	if (len < 0)
		len = 0;
	return (len);
}

static size_t	set_end(char const *s, char del)
{
	size_t	end;

	end = ft_strlen(s) - 1;
	while (ft_space(s[end], del))
		end--;
	return (end);
}

char	*ft_strtrim(char const *s, char del)
{
	size_t	start;
	size_t	end;
	int		i;
	char	*temp;
	int		len;

	i = 0;
	start = 0;
	if (!s)
		return (NULL);
	while (ft_space(s[start], del))
		start++;
	end = set_end(s, del);
	len = check_len(end, start);
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (NULL);
	while (start <= end && len > 0)
		temp[i++] = s[start++];
	temp[i] = '\0';
	return (temp);
}
