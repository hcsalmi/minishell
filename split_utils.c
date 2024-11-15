/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 00:40:38 by esirnio           #+#    #+#             */
/*   Updated: 2023/10/05 00:45:02 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_quote_state(char c, int quote_state)
{
	if (quote_state == 0 && c == '\'')
		return (1);
	else if (quote_state == 0 && c == '\"')
		return (2);
	else if (quote_state == 1 && c == '\'')
		return (0);
	else if (quote_state == 2 && c == '\"')
		return (0);
	else
		return (quote_state);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	skip_white_spaces(const char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

int	is_delimiter(char c, int *quote_state, int len)
{
	if (*quote_state == 0 && c == '|')
		return (1);
	if ((*quote_state == 2 && c == '\"') || (*quote_state == 1 && c == '\''))
	{
		*quote_state = 0;
		return (1);
	}
	if (*quote_state == 0 && c == ' ')
		return (1);
	if (*quote_state == 0 && (is_quote(c) || c == '|') && len > 2)
	{
		*quote_state = check_quote_state(c, *quote_state);
		return (1);
	}
	*quote_state = check_quote_state(c, *quote_state);
	return (0);
}
