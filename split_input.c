/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:36:24 by lsalmi            #+#    #+#             */
/*   Updated: 2023/10/05 22:18:05 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	how_many(const char *s, int i, int how_many, int *len)
{
	int	quote_state;

	quote_state = 0;
	while (s[i] != '\0')
	{
		if (is_delimiter(s[i], &quote_state, *len))
		{
			if (*len > 1 || s[i] == '|' || is_quote(s[i + 1]))
			{
				how_many++;
				if (s[i] == '|' && *len > 1)
					how_many++;
				*len = 1;
				if (is_quote(s[i]) && quote_state != 0)
					len++;
				i++;
				if (s[i] == ' ')
					i = skip_white_spaces(s, i);
				continue ;
			}
		}
		i++;
		(*len)++;
	}
	return (how_many);
}

static char	*do_str(const char *str, int len, int i)
{
	char	*temp;
	int		ind;
	int		tempi;

	ind = 0;
	tempi = i - len + 1;
	temp = (char *)malloc(len + 1);
	if (!temp)
		return (NULL);
	while ((ind + tempi) < (tempi + len))
	{
		temp[ind] = str[tempi + ind];
		ind++;
	}
	temp[ind] = '\0';
	return (temp);
}

int	take_string(int *len, t_data *data, const char *s, char **split)
{
	if (*len > 1 || s[data->idx] == '|')
	{
		if (*len > 1 && (!is_quote(s[data->idx]) || data->quote_state != 0))
		{
			split[data->word_idx] = do_str(s, *len - 1, data->idx - 1);
			if (split[data->word_idx] == NULL)
				return (-1);
			if (s[data->idx] == '|' && *len > 1)
				split[++data->word_idx] = do_str(s, 1, data->idx);
		}
		else
			split[data->word_idx] = do_str(s, *len, data->idx);
		if (split[data->word_idx++] == NULL)
			return (-1);
		*len = 1;
		if (is_quote(s[data->idx]) && data->quote_state != 0)
			(*len)++;
		data->idx++;
		if (s[data->idx] == ' ')
			data->idx = skip_white_spaces(s, data->idx);
	}
	return (1);
}

char	**split_split(char **split, const char *s, t_data *data)
{
	int	len;

	len = 1;
	data->quote_state = 0;
	data->idx = skip_white_spaces(s, data->idx);
	while (s[data->idx] != '\0')
	{
		if (is_delimiter(s[data->idx], &data->quote_state, len))
		{
			if (take_string(&len, data, s, split) == -1)
				return (ft_free_array(split));
			continue ;
		}
		data->idx++;
		len++;
	}
	if (len > 1)
	{
		split[data->word_idx] = do_str(s, len, data->idx);
		if (split[data->word_idx++] == NULL)
			return (ft_free_array(split));
	}
	return (split);
}

char	**split_input(char const *str, t_data *data)
{
	char	**split;
	int		count;
	int		i;
	int		len;

	if (!str)
		return (NULL);
	count = 0;
	i = 0;
	len = 1;
	i = skip_white_spaces(str, i);
	count = how_many(str, i, 0, &len);
	if (len > 1)
		count++;
	if (count < 1)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * count + 1);
	if (!split)
		malloc_error();
	split = split_split(split, (char *)str, data);
	split[count] = NULL;
	return (split);
}
