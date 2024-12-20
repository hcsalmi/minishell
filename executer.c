/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalmi <lsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:57:31 by lsalmi            #+#    #+#             */
/*   Updated: 2023/10/11 13:02:12 by lsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_the_way(t_node *tmp_node, t_data *data)
{
	char	*path;

	path = NULL;
	if (tmp_node->command[0][0] != '\0')
	{
		if (check_if_working_path(tmp_node->command[0]) == 1)
			return (1);
	}
	if (tmp_node->command[0][0] != '\0')
		path = set_path(tmp_node->command[0], data);
	if (path)
	{
		free(tmp_node->command[0]);
		tmp_node->command[0] = ft_strdup(path);
		free(path);
	}
	return (1);
}

void	exec_child(t_node *head, t_node *tmp_node, t_data *data)
{
	while (tmp_node && tmp_node->command && tmp_node->command[0] != NULL)
	{
		if (is_builtin(tmp_node->command[0]) == -1)
		{
			if (find_the_way(tmp_node, data) == -1)
			{
				tmp_node = tmp_node->next;
				continue ;
			}
		}
		signal(SIGINT, SIG_IGN);
		tmp_node->pid = fork();
		if (tmp_node->pid == -1)
			exit_error("StayFreshCheeseBags: fork error\n");
		if (tmp_node->pid == 0)
			ft_child(tmp_node, data);
		close_current_fds(tmp_node);
		if (tmp_node->pid > 0)
			tmp_node = tmp_node->next;
	}
	ft_wait(head, data);
	signal(SIGINT, ctrl_c_main);
	return ;
}

void	exec(t_node *head, t_data *data)
{
	t_node	*tmp_node;

	tmp_node = head;
	if (head->next == NULL && is_builtin(head->command[0]) == 1
		&& head->write_fd == 1 && head->read_fd == 0)
	{
		do_builtin(head, data);
		return ;
	}
	signal(SIGINT, ctrl_c_child);
	exec_child(head, tmp_node, data);
}
