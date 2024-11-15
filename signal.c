/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esirnio <esirnio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:19:16 by lsalmi            #+#    #+#             */
/*   Updated: 2023/10/11 13:41:13 by esirnio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_signals(void)
{
	signal(SIGINT, ctrl_c_main);
	signal(SIGQUIT, SIG_IGN);
}

void	enable_echo_ctrl_c(struct termios *termios)
{
	termios->c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, termios);
}

void	disable_echo_ctrl_c(struct termios *termios)
{
	termios->c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, termios);
}

void	ctrl_c_main(int signal)
{
	(void)signal;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	ctrl_c_child(int signal)
{
	if (signal != SIGINT)
		return ;
	write(1, "\n", 1);
}
