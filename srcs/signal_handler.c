/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:03:54 by dummy             #+#    #+#             */
/*   Updated: 2023/07/22 18:20:37 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_signal.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int	g_recived_signal_id;

void	cmd_exec_signal_handler(int sig_id)
{
	g_recived_signal_id = sig_id;
}

void	heredoc_child_signal_handler(int sig_id)
{
	if (sig_id == SIGINT)
		exit(0);
	rl_redisplay();
}

void	readline_signal_handler(int sig_id)
{
	g_recived_signal_id = sig_id;
	if (sig_id == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	if (sig_id == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	rl_redisplay();
}

void	signal_handler(int sig_id)
{
	g_recived_signal_id = sig_id;
	if (sig_id == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
}

void	register_signal_handler(void (*handler)(int))
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}
