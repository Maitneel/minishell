/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:34:42 by taksaito          #+#    #+#             */
/*   Updated: 2023/05/19 20:110:01 by taksaito         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envs)
{
	t_token_manager	*token_manager;
	t_env_manager	*env_manager;
	// t_token			*token;
	// t_env			*env;
	t_command *command;


	signal(SIGINT, resive_signal);
	signal(SIGQUIT, resive_signal);
	g_signal_info.status = UNDEFINED;
	g_signal_info.pid_list = NULL;
	env_manager = new_env_manager(envs);
	// ここのエラー処理、xcallocにしたのでおそらく消せるが、new_env_managerの処理がエグそうなので消して大丈夫かわからない
	if (env_manager == NULL)
	{
		return (1);
	}
	// env = env_manager->front;
	while (true)
	{
		token_manager = prompt(env_manager);
		if (token_manager == NULL)
		{
			// prompt 関数内でエラーメッセージの出力が完了しているので、そのままbreakしexitする
			// このエラー処理はreadlineがNULLを返した時(Cntl+Dの時)に必要なのでいる
			break ;
		}
		command = parse(token_manager);
		if (command == NULL)
		{
			// ここはおそらくいらない
			// TODO ここでエラーメッセージの出力をするか、parser関数ない出力するか
			break;
		}
		if (command->is_error)
		{
			// printf("minishell: syntax error\n");
			continue;
		} 
		else if (command->command_name != NULL && strcmp(command->command_name, "exit") == 0 && command->next_pipe == 0)
		{
			char **args;
			args = make_args(command);
			env_manager->exit_status = command_exit(env_manager, args);
			free_string_array(args);
			continue;
		}
		else 
		{
			print_command(command);
			command_exec(command, env_manager);
		}
		free_command(command);
		free_token_manager(token_manager);
	}
	free_token_manager(token_manager);
	free_env_manager(env_manager);
	(void)argc;
	(void)argv;
	(void)envs;
}


void check_fd(void) {
	for (size_t i = 3; i < 10000; i++) {
		if(close(i) == 0) {
			fprintf(stderr, "\x1b[35m");
			fprintf(stderr, "close %5zu\n", i);
			fprintf(stderr, "\x1b[39m");
		}
	}
}

__attribute__((destructor)) void destructor()
{
	// check_fd();
	// system("leaks minishell -q > /dev/stderr/");
}
