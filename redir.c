/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalmi <lsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:21:37 by lsalmi            #+#    #+#             */
/*   Updated: 2023/10/06 16:11:19 by lsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_open(t_data *data, int fd)
{
	if (fd < 0)
	{
		write(2, "StayFreshCheeseBags: open error\n", 32);
		data->exit_status = 1;
	}
}

void	open_write_fd(t_tokens *token, t_node **node)
{
	if (token->next->type == WORD && token->type == RDR_R)
		(*node)->write_fd = \
			open(token->next->str, O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (token->next->type == WORD && token->type == RDR_RR)
		(*node)->write_fd = \
			open(token->next->str, O_RDWR | O_CREAT | O_APPEND, 0664);
}

int	left_rdr(t_tokens *token, t_node **node, t_data *data)
{
	if (token && token->type == RDR_L)
	{
		if (token->next->type == WORD)
		{
			if ((*node)->read_fd != 0)
				close((*node)->read_fd);
			(*node)->read_fd = open(token->next->str, O_RDWR, 0664);
		}
		check_open(data, (*node)->read_fd);
		return (1);
	}
	else if (token && token->type == RDR_LL)
	{
		if ((*node)->read_fd != 0)
			close((*node)->read_fd);
		token = token->next;
		data->heredoc_count++;
		(*node)->read_fd = here_doc(token->str, data);
		check_open(data, (*node)->read_fd);
		token = token->next;
		return (1);
	}
	return (-1);
}

int	is_redir(t_tokens *token, t_node **node, t_data *data)
{
	if (token && (token->type == RDR_R || token->type == RDR_RR))
	{
		open_write_fd(token, node);
		check_open(data, (*node)->write_fd);
		return (1);
	}
	else if (token && (token->type == RDR_L || token->type == RDR_LL))
		return (left_rdr(token, node, data));
	return (-1);
}
