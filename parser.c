/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 19:33:23 by lsalmi            #+#    #+#             */
/*   Updated: 2023/10/11 12:33:17 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*make_node(int r_fd)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		malloc_error();
	node->read_fd = r_fd;
	node->write_fd = 1;
	node->next = NULL;
	node->command = NULL;
	return (node);
}

void	do_pipe(t_node *current, int *r_fd)
{
	int	fds[2];

	if (pipe(fds) == -1)
	{
		write(2, "StayFreshCheeseBags: pipe error\n", 32);
		exit(112);
	}
	if (current->write_fd == 1)
		current->write_fd = fds[1];
	else
	{
		if (close(fds[1]) == -1)
			exit_error("StayFreshCheeseBags: close error\n");
	}
	*r_fd = fds[0];
}

void	make_cmd_and_pipes(t_tokens *tokens, t_data *data, t_node *head)
{
	t_node	*temp_node;
	int		r_fd;

	temp_node = NULL;
	temp_node = head;
	r_fd = 0;
	while (tokens)
	{
		if (is_redir(tokens, &temp_node, data) == 1)
			tokens = tokens->next;
		else if (tokens && tokens->type == PIPE && head)
		{
			do_pipe(temp_node, &r_fd);
			temp_node->next = make_node(r_fd);
			temp_node = temp_node->next;
		}
		else if (tokens->type == CMD)
			temp_node->command = make_command_to_node(tokens, data);
		if (tokens)
			tokens = tokens->next;
	}
}

t_node	*parser(t_tokens *tokens, t_data *data)
{
	t_node	*head;

	head = make_node(0);
	make_cmd_and_pipes(tokens, data, head);
	return (head);
}
