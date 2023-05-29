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

#include <readline/history.h>
#include <readline/readline.h>

#include "env.h"
#include "prompt.h"
#include "parser.h"

int	main(int argc, char **argv, char **envs)
{
	t_token_manager	*token_manager;
	t_env_manager	*env_manager;
	t_token			*token;
	t_env			*env;
    t_command *command;

	env_manager = new_env_manager(envs);
	if (env_manager == NULL)
	{
		return (1);
	}
	env = env_manager->front;
	while (true)
	{
		token_manager = prompt(env_manager);
		if (token_manager == NULL)
		{
			// TODO なんかのしょり
			printf("tokenize error\n");
			break ;
		}
		token = token_manager->front;
		if (token == NULL)
			break ;
		if (strcmp(token->word, "exit") == 0)
			break ;
		while (token != NULL)
		{
			printf("%s %d", token->word, token->kind);
            if (token->kind == SYNTAX_ERROR)
            {
                fprintf(stdout, "\x1b[35m");
                printf(" syntax error");
                fprintf(stdout, "\x1b[39m");
            }
			token = token->next;
            printf("\n");
		}
        command = parse(token_manager);
		if (command->is_error)
		{
			printf("minishell: syntax error\n");
		}
        print_command(command);
        free_command(command);
		free_token_manager(token_manager);
	}
	free_token_manager(token_manager);
	free_env_manager(env_manager);
	(void)argc;
	(void)argv;
	(void)envs;
	(void)env;
}


// __attribute__((destructor)) void destructor()
// {
// 	system("leaks minishell -q");
// }
