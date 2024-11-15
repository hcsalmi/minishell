/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:00:08 by esirnio           #+#    #+#             */
/*   Updated: 2023/10/11 12:43:18 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe(char *token)
{
	if (ft_strcmp(token, "|") == 0)
		return (1);
	return (0);
}

int	lexer_is_redirect(char *token)
{
	if (ft_strcmp(token, ">>") == 0)
		return (7);
	if (ft_strcmp(token, ">") == 0)
		return (5);
	if (ft_strcmp(token, "<<") == 0)
		return (8);
	if (ft_strcmp(token, "<") == 0)
		return (6);
	return (0);
}

int	define_type(char *token, int found_cmd, char **splitted, int i)
{
	static int	looking_for_file;

	if (lexer_is_redirect(token) != 0)
	{
		if (splitted[i + 1])
			looking_for_file = 1;
		return (lexer_is_redirect(token));
	}
	if (is_pipe(token) == 1)
	{
		looking_for_file = 0;
		return (PIPE);
	}
	if (looking_for_file)
	{
		looking_for_file = 0;
		return (WORD);
	}
	if (!found_cmd)
		return (CMD);
	else
		return (WORD);
	return (-1);
}

char	*trim_quotes(char *str, t_tokens *token)
{
	if (str[0] == '\"' )
		return (ft_strtrim(str, '\"'));
	if (str[0] == '\'')
	{
		token->dont_expand = 1;
		return (ft_strtrim(str, '\''));
	}
	return (NULL);
}
