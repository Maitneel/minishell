/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:34:42 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/09 21:10:59 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <readline/history.h>
#include <readline/readline.h>

#include "env.h"
#include "prompt.h"
#include "parser.h"
#include "ft_signal.h"
#include "command_exec.h"
#include "builtin.h"

void	setup_signal(void)
{
	signal(SIGINT, resive_signal);
	signal(SIGQUIT, resive_signal);
	g_signal_info.status = UNDEFINED;
	g_signal_info.resived_sigid = -1;
	g_signal_info.pid_list = NULL;
}

#define LOOP_CONTINUE 0
#define LOOP_BREAK 1

int	shell_loop(t_env_manager *env_manager)
{
	t_token_manager	*token_manager;
	t_command		*command;

	token_manager = prompt(env_manager);
	if (token_manager == NULL)
		return (LOOP_BREAK);
	command = parse(token_manager, env_manager);
	if (command == NULL)
	{
		free_token_manager(token_manager);
		return (LOOP_BREAK);
	}
	if (command->is_error || command->is_heredoc_error)
	{
		free_token_manager(token_manager);
		free_command(command);
		return (LOOP_CONTINUE);
	}
	command_exec(command, env_manager);
	free_token_manager(token_manager);
	free_command(command);
	return (LOOP_CONTINUE);
}

int	main(int argc, char **argv, char **envs)
{
	t_env_manager	*env_manager;
	int				status_code;

	(void)argc;
	(void)argv;
	setup_signal();
	env_manager = new_env_manager(envs);
	if (env_manager == NULL)
	{
		return (1);
	}
	while (shell_loop(env_manager) == LOOP_CONTINUE)
		;
	status_code = env_manager->exit_status;
	free_env_manager(env_manager);
	return (status_code);
}
