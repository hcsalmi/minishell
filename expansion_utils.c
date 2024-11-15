/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalmi <lsalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:24:02 by lsalmi            #+#    #+#             */
/*   Updated: 2023/10/06 21:24:03 by lsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*shell_strjoin(char *s1, char *s2)
{
	char	*ret;

	ret = NULL;
	ret = ft_strjoin(s1, s2);
	if (!ret)
		malloc_error();
	free(s1);
	return (ret);
}

int	stuff_in_between(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (ft_isalnum(s[i]) == 1 || s[i] == '?' || s[i] == '_'))
	{
		i++;
	}
	if (s[i] && s[i] != '$')
		return (1);
	return (0);
}

char	*sort_stuff_in_between(char *expanded_var, char *s)
{
	int		i;
	char	c;

	i = 0;
	while (s[i] && (ft_isalnum(s[i]) == 1 || s[i] == '?' || s[i] == '_'))
		i++;
	while (s[i] && s[i] != '$')
	{
		c = s[i];
		expanded_var = shell_strjoin(expanded_var, &c);
		i++;
	}
	return (expanded_var);
}
