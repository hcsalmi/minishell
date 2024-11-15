/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:00:08 by esirnio           #+#    #+#             */
/*   Updated: 2023/10/06 18:23:42 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*new_lexer_node(int found_cmd, char **splitted_input, int i)
{
	t_tokens	*new;
	char		*temp;

	new = NULL;
	temp = NULL;
	new = (t_tokens *)malloc(sizeof(t_tokens));
	if (!new)
		malloc_error();
	new->dont_expand = 0;
	if (splitted_input[i][0] == '\"' || splitted_input[i][0] == '\'')
	{
		temp = trim_quotes(splitted_input[i], new);
		if (!temp)
			malloc_error();
		new->str = ft_strdup(temp);
		free(temp);
	}
	else
		new->str = ft_strdup(splitted_input[i]);
	if (!new->str)
		malloc_error();
	new->type = define_type(new->str, found_cmd, splitted_input, i);
	new->next = NULL;
	return (new);
}

int	check_quotes(char *str, t_data *data, int i)
{
	char	quote_state;

	if (strchr_idx(str, '\"') == -1 && strchr_idx(str, '\'') == -1)
		return (0);
	quote_state = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && quote_state == 0)
			quote_state = 1;
		else if (str[i] == '\"' && quote_state == 0)
			quote_state = 2;
		else if (str[i] == '\'' && quote_state == 1)
			quote_state = 0;
		else if (str[i] == '\"' && quote_state == 2)
			quote_state = 0;
		i++;
	}
	if (quote_state != 0)
	{
		write(2, "StayFreshCheeseBags: ", 21);
		write(2, "unexpected EOF while looking for matching `\"'\n", 46);
		data->exit_status = 258;
		return (-1);
	}
	return (0);
}

int	check_syntax_for_tokens(t_tokens *tokens, t_data *data)
{
	t_tokens	*temp;

	temp = tokens;
	while (temp)
	{
		if (tokens->type == PIPE || (temp->type == PIPE \
			&& (temp->next == NULL || temp->next->type == PIPE)))
		{
			syntax_error_near_token(data);
			return (-1);
		}
		else if (temp->type == RDR_R || temp->type == RDR_L
			|| temp->type == RDR_RR || temp->type == RDR_LL)
		{
			if (temp->next == NULL || temp->next->type != WORD)
			{
				syntax_error_near_token(data);
				return (-1);
			}
		}
		temp = temp->next;
	}
	return (0);
}

void	create_tokens(t_data *data, char **splitted_input)
{
	int			i;
	int			found_cmd;
	t_tokens	*temp;
	t_tokens	*new_token;

	new_token = NULL;
	i = 0;
	found_cmd = 0;
	data->tokens = new_lexer_node(found_cmd, splitted_input, i);
	if (data->tokens->type == CMD)
		found_cmd = 1;
	temp = data->tokens;
	i++;
	while (splitted_input && splitted_input[i] != NULL)
	{
		new_token = new_lexer_node(found_cmd, splitted_input, i);
		i++;
		if (new_token->type == CMD)
			found_cmd = 1;
		if (new_token->type == PIPE)
			found_cmd = 0;
		temp->next = new_token;
		temp = temp->next;
	}
}

int	lexer(char *input, t_data *data)
{
	char		**splitted_input;

	if (check_quotes(input, data, 0) == -1)
		return (-1);
	data->word_idx = 0;
	data->idx = 0;
	splitted_input = split_input(input, data);
	if (!splitted_input)
		return (-1);
	create_tokens(data, splitted_input);
	ft_free_array(splitted_input);
	if (check_syntax_for_tokens(data->tokens, data) == -1)
		return (-1);
	data->nodes = parser(data->tokens, data);
	if (data->nodes->command == NULL)
		return (-1);
	return (1);
}
