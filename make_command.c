/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 19:33:23 by lsalmi            #+#    #+#             */
/*   Updated: 2023/10/06 18:27:24 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_command(int count, t_tokens *token_head, t_data *data, int i)
{
	char		**command;
	t_tokens	*temp_token;

	command = NULL;
	command = (char **)malloc(sizeof(char *) * (count + 1));
	if (!command)
		malloc_error();
	temp_token = token_head;
	while (i < count)
	{
		if (temp_token->type == WORD || temp_token->type == CMD)
		{
			if (strchr_idx(temp_token->str, '$') != -1)
				do_expansion(temp_token, data);
			command[i] = ft_strdup(temp_token->str);
			if (command[i] == NULL)
				data->exit_status = 666;
			i++;
		}
		else
			temp_token = temp_token->next;
		if (temp_token && temp_token->type != PIPE)
			temp_token = temp_token->next;
	}
	return (command);
}

int	count_words(t_tokens *token)
{
	t_tokens	*temp_token;
	int			count;

	count = 0;
	temp_token = token;
	while (temp_token && temp_token->type != PIPE)
	{
		if (temp_token->type == WORD || temp_token->type == CMD)
		{
			count++;
			temp_token = temp_token->next;
		}
		else
		{
			temp_token = temp_token->next;
			if (temp_token)
				temp_token = temp_token->next;
		}
	}
	return (count);
}

char	**make_command_to_node(t_tokens *token, t_data *data)
{
	int		count;
	char	**command;
	int		i;

	count = 0;
	i = 0;
	count = count_words(token);
	command = make_command(count, token, data, i);
	command[count] = NULL;
	return (command);
}
