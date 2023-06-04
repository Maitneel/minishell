/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 18:11:20 by taksaito          #+#    #+#             */
/*   Updated: 2023/06/04 20:48:18 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "env.h"
#include "ft_signal.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define WRITE_FD 1
#define READ_FD 0

char **make_args(t_command *command)
{
	char **args = malloc(sizeof(char *) * 3);
	args[0] = strdup("echo");
	args[1] = strdup("hoge");
	args[2] = NULL;
	(void)command;
	return args;
}


char *find_path(t_command *command, t_env_manager *env_manager)
{
	// TODO: implement;
	(void)command;
	(void)env_manager;
	return strdup("/bin/echo");
}

int ft_exec(t_command *command, t_env_manager *env_manager)
{
	char	*command_path;
	command_path = find_path(command, env_manager);
	if (command_path == NULL)
	{
		return (-1);
	}
	// TODO: envの$?に入れる　
	execve(command_path, make_args(command), make_env_ptr(env_manager));
	return 0;
}

int pipe_exec(int before_fd, t_command *command, t_env_manager *env_manager)
{
	int pipe_fd[2];
	pid_t pid;

	pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid_push_back(&signal_info.pid_list, pid) == NULL)
		return (-1);
	if (pid == 0)
	{
		//child
		dup2(before_fd, STDIN_FILENO);
		dup2(pipe_fd[WRITE_FD], STDOUT_FILENO);
		close(before_fd);
		ft_exec(command, env_manager);
		close(pipe_fd[WRITE_FD]);
		exit(0); // ?
	} else 
	{
		// parent
		close(before_fd);
		close(pipe_fd[WRITE_FD]);
		// TODO: append process id
	}
	return (pipe_fd[READ_FD]);
}

int non_pipe_exec(int before_fd, t_command *command, t_env_manager *env_manager)
{
	pid_t pid;
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid_push_back(&signal_info.pid_list, pid) == NULL)
		return (-1);
	if (pid == 0)
	{
		//child
		dup2(before_fd, STDIN_FILENO);
		if (before_fd != STDIN_FILENO)
			close(before_fd);
		ft_exec(command, env_manager);
		exit(0);
	} else
	{
		// parent
		if (before_fd != STDIN_FILENO)
			close(before_fd);
		return (STDIN_FILENO);
	}
	return (STDIN_FILENO);
}

int	command_exec(t_command *commands, t_env_manager *env_manager)
{
	t_command	*current;
	t_pid_list	*pid_current;
	int			before_fd;

	current = commands;
	before_fd = STDIN_FILENO;
	while (current != NULL)
	{
		if (current->next_pipe)
		{
			before_fd = pipe_exec(before_fd, current, env_manager);
		} else {
			before_fd = non_pipe_exec(before_fd, current, env_manager);
		}
		current = current->next;
	}

	pid_current = signal_info.pid_list;
	while (pid_current != NULL)
	{
		printf("waiting\n");
		int tmp;
		wait(&tmp);
		pid_current = pid_current->next;
	}
	return (0);
}
