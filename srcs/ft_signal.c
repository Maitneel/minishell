/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:13:58 by dummy             #+#    #+#             */
/*   Updated: 2023/07/17 17:27:26 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_signal.h"
#include "ft_xcalloc.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stddef.h>
#include <readline/readline.h>

void	resive_signal(int sig_id)
{
	if (!(sig_id == SIGINT || sig_id == SIGQUIT))
		return ;
	if (sig_id != SIGQUIT)
		write(STDOUT_FILENO, "\n", 1);
	if (g_signal_info.status == READING_PROMPT)
	{
		if (sig_id == SIGINT)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
		}
		rl_redisplay();
		*(g_signal_info.exit_status) = 1;
	}
	else if (g_signal_info.status == READING_HEREDOC && sig_id == SIGINT)
	{
		g_signal_info.resived_sigid = sig_id;
		close(g_signal_info.heredoc_fd);
		g_signal_info.heredoc_fd = -1;
	}
}

t_pid_list	*new_pid_list(pid_t pid)
{
	t_pid_list	*pid_list;

	pid_list = ft_xcalloc(1, sizeof(t_pid_list));
	if (pid_list == NULL)
		return (NULL);
	pid_list->pid = pid;
	return (pid_list);
}

void	*free_pid_list(t_pid_list **pid_list)
{
	t_pid_list	*current;
	t_pid_list	*next;

	current = *pid_list;
	(*pid_list) = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = NULL;
		free(current);
		current = next;
	}
	return (NULL);
}

t_pid_list	*pid_push_back(t_pid_list **list, pid_t pid)
{
	t_pid_list	*current;

	if (list == NULL)
		return (NULL);
	if (*list == NULL)
	{
		*list = new_pid_list(pid);
		return (*list);
	}
	current = *list;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new_pid_list(pid);
	if (current->next == NULL)
	{
		return (free_pid_list(list));
	}
	return (*list);
}
