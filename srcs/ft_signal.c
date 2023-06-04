/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:13:58 by dummy             #+#    #+#             */
/*   Updated: 2023/06/01 15:32:21 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_signal.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>

void	resive_signal(int sig_id)
{
	if (!(sig_id == SIGINT || sig_id == SIGQUIT))
		return ;
	if (signal_info.status == READING_PROMPT)
	{
		rl_on_new_line();
        write(STDIN_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
