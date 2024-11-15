/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:01:11 by esirnio           #+#    #+#             */
/*   Updated: 2023/10/11 13:02:25 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	take_envs(char **envs, t_data *data)
{
	int	len;
	int	i;

	i = -1;
	len = count_envs(envs);
	data->envs = (char **)malloc(sizeof(char *) * (len + 1));
	if (!data->envs)
		malloc_error();
	while (++i < len)
		data->envs[i] = ft_strdup(envs[i]);
	data->envs[i] = NULL;
}

void	free_nodes(t_node **nodes)
{
	t_node	*temp;

	temp = NULL;
	while (*nodes)
	{
		temp = *nodes;
		*nodes = (*nodes)->next;
		if (temp->command != NULL)
			ft_free_array(temp->command);
		if (temp)
			free(temp);
	}
	*nodes = NULL;
}

void	free_tokens(t_tokens **tokens)
{
	t_tokens	*temp;

	while (*tokens)
	{
		temp = *tokens;
		*tokens = (*tokens)->next;
		free(temp->str);
		free(temp);
	}
	*tokens = NULL;
}

void	minishell(t_data *data, struct termios *termios)
{
	char			*input;

	disable_echo_ctrl_c(termios);
	input = readline("StayFreshCheeseBags: ");
	enable_echo_ctrl_c(termios);
	if (!input)
	{
		write(1, "exit\n", 5);
		exit(data->exit_status);
	}
	if (ft_strlen(input) > 0)
		add_history(input);
	if (input[0] != '\0')
	{
		if (lexer(input, data) == 1)
		{
			exec(data->nodes, data);
			close_current_fds(data->nodes);
		}
	}
	ft_bzero(input, ft_strlen(input));
	free(input);
}

int	main(int argc, char **argv, char **env)
{
	t_data			data;
	struct termios	termios;

	(void)argv;
	if (argc != 1)
		return (-1);
	init_signals();
	take_envs(env, &data);
	data.exit_status = 0;
	data.nodes = NULL;
	data.tokens = NULL;
	data.heredoc_count = 0;
	tcgetattr(0, &termios);
	while (1)
	{
		minishell(&data, &termios);
		remove_here_doc_files(&data);
		free_tokens(&data.tokens);
		free(data.tokens);
		free_nodes(&data.nodes);
		free(data.nodes);
	}
	return (0);
}
