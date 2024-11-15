/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:13:46 by esirnio           #+#    #+#             */
/*   Updated: 2023/10/03 17:29:23 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_echo(t_node *node, t_data *data)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (node->command[i] != NULL && ft_strcmp(node->command[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (node->command[i])
	{
		write(1, node->command[i], ft_strlen(node->command[i]));
		i++;
		if (node->command[i])
			write(1, " ", 1);
	}
	if (newline == 1)
		write(1, "\n", 1);
	data->exit_status = 0;
	return (0);
}
