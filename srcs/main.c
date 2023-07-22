/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:34:42 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/22 16:33:53 by dummy            ###   ########.fr       */
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
#include "signal_handler.h"

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
	env_manager = new_env_manager(envs);
	if (env_manager == NULL)
	{
		return (1);
	}
	register_signal_handler(signal_handler);
	g_recived_signal_id = -1;
	while (shell_loop(env_manager) == LOOP_CONTINUE)
		;
	status_code = env_manager->exit_status;
	free_env_manager(env_manager);
	return (status_code);
}
