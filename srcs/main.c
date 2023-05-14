/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:34:42 by taksaito          #+#    #+#             */
/*   Updated: 2023/05/14 15:58:41 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "prompt.h"

int	main(int argc, char **argv, char ** envs)
{
	char *line;
	while (true)
	{
		line = prompt();
		if(strcmp(line, "exit") == 0)
			break;
		free(line);
	}
	free(line);
	(void)argc;
	(void)argv;
	(void)envs;
}

__attribute__((destructor))
void destructor() {
	system("leaks minishell");
}
