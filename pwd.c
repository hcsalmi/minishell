/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:54:21 by esirnio           #+#    #+#             */
/*   Updated: 2023/10/06 19:22:15 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(void)
{
	char	path[1024];

	if (getcwd(path, sizeof(path)) == NULL)
		return (NULL);
	return (ft_strdup(path));
}

void	do_pwd(t_data *data)
{
	char	*pwd;

	pwd = get_path();
	if (!pwd)
	{
		write(2, "StayFreshCheeseBags: getcwd error\n", 34);
		data->exit_status = 1;
		return ;
	}
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
}
