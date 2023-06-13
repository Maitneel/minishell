/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:13:58 by dummy             #+#    #+#             */
/*   Updated: 2023/06/13 20:47:33 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_signal.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stddef.h>
#include <readline/readline.h>

void	resive_signal(int sig_id)
{
	// t_pid_list *pid;

	if (!(sig_id == SIGINT || sig_id == SIGQUIT))
		return ;
	if (signal_info.status == READING_PROMPT)
	{
		rl_on_new_line();
		write(STDIN_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal_info.status == EXECUTING_COMMAND)
	{
		// pid = signal_info.pid_list;
		// while (pid != NULL)
		// {
		// 	kill(pid->pid, sig_id);
		// 	pid = pid->next;
		// }
	}
}


t_pid_list *new_pid_list(pid_t pid)
{
	t_pid_list *pid_list;
	pid_list = calloc(1, sizeof(t_pid_list));
	if (pid_list == NULL)
		return NULL;
	pid_list->pid = pid;
	return pid_list;
}

void *free_pid_list(t_pid_list **pid_list)
{
	t_pid_list *current;
	t_pid_list *next;

	current = *pid_list;
	(*pid_list) = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = NULL;
		free(current);
		current = next;
	}
	return NULL;
}

t_pid_list    *pid_push_back(t_pid_list **list, pid_t pid)
{
	t_pid_list *current;
	
	if (list == NULL)
		return NULL;

	if (*list == NULL)
	{
		*list = new_pid_list(pid);
		return *list;
	}
	current = *list;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new_pid_list(pid);
	if (current->next == NULL) {
		return free_pid_list(list);
	}
	return *list;
}


t_pid_list *new_pid_list(pid_t pid)
{
	t_pid_list *pid_list;
	pid_list = calloc(1, sizeof(t_pid_list));
	if (pid_list == NULL)
		return NULL;
	pid_list->pid = pid;
	return pid_list;
}

void *free_pid_list(t_pid_list **pid_list)
{
	t_pid_list *current;
	t_pid_list *next;

	current = *pid_list;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	return NULL;
}

t_pid_list    *pid_push_back(t_pid_list **list, pid_t pid)
{
	t_pid_list *current;
	
	if (list == NULL)
		return NULL;

	if (*list == NULL)
	{
		*list = new_pid_list(pid);
		return *list;
	}
	current = *list;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new_pid_list(pid);
	if (current->next == NULL) {
		return free_pid_list(list);
	}
	return *list;
}
