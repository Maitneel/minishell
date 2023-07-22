/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:03:54 by dummy             #+#    #+#             */
/*   Updated: 2023/07/22 17:06:36 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "ft_signal.h"

// void	resive_signal(int sig_id)
// {
// 	if (!(sig_id == SIGINT || sig_id == SIGQUIT))
// 		return ;
// 	if (sig_id != SIGQUIT)
// 		write(STDOUT_FILENO, "\n", 1);
// 	if (g_signal_info.status == READING_PROMPT)
// 	{
// 		if (sig_id == SIGINT)
// 		{
// 			rl_on_new_line();
// 			rl_replace_line("", 0);
// 		}
// 		rl_redisplay();
// 		*(g_signal_info.exit_status) = 1;
// 	}
// 	else if (g_signal_info.status == READING_HEREDOC && sig_id == SIGINT)
// 	{
// 		g_signal_info.resived_sigid = sig_id;
// 		close(g_signal_info.heredoc_fd);
// 		g_signal_info.heredoc_fd = -1;
// 	}
// }

void	heredoc_signal_handler(int sig_id)
{
	if (sig_id == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	write(1, "hogehoge\n", 9);
	g_recived_signal_id = sig_id;
}

void	heredoc_child_signal_handler(int sig_id)
{
	if (sig_id == SIGINT)
		exit(0);
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

void register_signal_handler(void(*handler)(int))
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}