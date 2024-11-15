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

char	*get_current_var(char *s)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	ret = NULL;
	while (s[i] && (ft_isalnum(s[i]) == 1 || s[i] == '?' || s[i] == '_'))
		i++;
	if (s[i])
	{
		ret = (char *)malloc(sizeof(char) * (i + 1));
		if (!ret)
			malloc_error();
		ret[i] = '\0';
		while (j < i)
		{
			ret[j] = s[j];
			j++;
		}
		return (ret);
	}
	return (s);
}

int	next_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			return (i);
		}
		i++;
	}
	return (i);
}

char	*expand_var(char *str, t_data *d, int i)
{
	char	*var;

	var = NULL;
	while (d->envs[i])
	{
		if (find_env(get_current_var(str), d->envs[i]) == 1)
		{
			if (str[0] != '?')
				var = ft_strdup(d->envs[i] + strchr_idx(d->envs[i], '=') + 1);
			else if (str[0] == '?')
				var = ft_strdup(ft_itoa(d->exit_status));
			if (!var)
				malloc_error();
			if (ft_strchr(str, '$'))
			{
				if (stuff_in_between(str))
					var = sort_stuff_in_between(var, str);
				var = shell_strjoin(var, expand_var(str + next_var(str), d, 0));
			}
			else if (stuff_in_between(str))
				var = sort_stuff_in_between(var, str);
		}
		i++;
	}
	return (var);
}

void	do_expansion(t_tokens *token, t_data *data)
{
	char	*str;
	char	*expanded;

	str = NULL;
	expanded = NULL;
	if (strchr_idx(token->str, '$') != 0)
	{
		str = ft_strndup(token->str, strchr_idx(token->str, '$'));
		if (!str)
			malloc_error();
	}
	if (!token->dont_expand)
		expanded = expand_var(token->str + strchr_idx(token->str, '$') + 1, \
		data, 0);
	else
		expanded = ft_strdup(token->str);
	if (expanded != NULL && !token->dont_expand)
	{
		free(token->str);
		token->str = ft_strjoin(str, expanded);
		if (token->str == NULL)
			data->exit_status = 666;
		free(str);
	}
}
