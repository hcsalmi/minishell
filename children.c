/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsalmi <lsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:21:04 by lsalmi            #+#    #+#             */
/*   Updated: 2023/10/06 17:40:48 by lsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit_child_process(int signal)
{
	write(2, "Quit: ", 6);
	write(2, ft_itoa(signal), ft_strlen(ft_itoa(signal)));
	write(2, "\n", 1);
}

void	ft_wait(t_node *head, t_data *data)
{
	int	status;
	int	signal;
	int	once;

	once = 0;
	while (head)
	{
		waitpid(head->pid, &status, WUNTRACED);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status) && once == 0)
		{
			once = 1;
			signal = WTERMSIG(status);
			if (signal == SIGQUIT)
				quit_child_process(signal);
			if (signal == SIGSEGV)
				write(2, "Segmentation fault: 11\n", 23);
			if (signal == SIGINT)
				write(2, "\n", 1);
			data->exit_status = 128 + signal;
		}
		head = head->next;
	}
}

void	close_current_fds(t_node *node)
{
	if (node->write_fd != 1)
	{
		if (close(node->write_fd) == -1)
			exit_error("StayFreshCheeseBags: close error\n");
		node->write_fd = 1;
	}
	if (node->read_fd != 0)
	{
		if (close(node->read_fd) == -1)
			exit_error("StayFreshCheeseBags: close error\n");
		node->read_fd = 0;
	}
}

void	close_other_fds(t_node *nodes, t_node *cur)
{
	t_node	*loop;

	loop = nodes;
	while (loop)
	{
		if (loop->read_fd == cur->read_fd || loop->write_fd == cur->write_fd)
		{
			loop = loop->next;
			continue ;
		}
		if (loop->read_fd != 0)
		{
			if (close(loop->read_fd) == -1)
				exit_error("StayFreshCheeseBags: close error\n");
			loop->read_fd = 0;
		}
		if (loop->write_fd != 1)
		{
			if (close(loop->write_fd) == -1)
				exit_error("StayFreshCheeseBags: close error\n");
			loop->write_fd = 1;
		}
		loop = loop->next;
	}
}

int	ft_child(t_node *node, t_data *data)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (node->read_fd != 0)
	{
		if (dup2(node->read_fd, 0) < 0)
			exit_error("StayFreshCheeseBags: dup2 error\n");
	}
	if (node->write_fd != 1)
	{
		if (dup2(node->write_fd, 1) < 0)
			exit_error("StayFreshCheeseBags: dup2 error\n");
	}
	close_other_fds(data->nodes, node);
	if (is_builtin(node->command[0]) == 1)
	{
		do_builtin(node, data);
		close_current_fds(node);
		exit(0);
	}
	if (execve(node->command[0], node->command, data->envs) < 0)
		execve_error(node);
	close_current_fds(node);
	exit(0);
}
