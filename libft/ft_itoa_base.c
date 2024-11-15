/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 13:40:54 by esirnio           #+#    #+#             */
/*   Updated: 2022/10/11 15:45:28 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(long long value, int base)
{
	static char	hex[] = "0123456789abcdef";
	static char	buf[50];
	char		*ret;
	int			i;

	if (base == 10 && value == -9223372036854775807 - 1)
		return ("-9223372036854775808");
	ret = &buf[49];
	*ret = '\0';
	if (value < 0 && base == 10)
	{
		value = value * -1;
		i = -1;
	}
	else
		i = 1;
	while (value != 0)
	{
		ret--;
		*ret = hex[value % base];
		value = value / base;
	}
	if (i == -1)
		*--ret = '-';
	return (ret);
}
