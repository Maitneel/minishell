/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */	
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:27:47 by dummy             #+#    #+#             */
/*   Updated: 2023/05/29 19:52:09 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "tokenize.h"
#include "expand_env.h"
#include <errno.h>
#include "ft_signal.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdlib.h>



static void	*free_with_return_null(void *ptr)
{
	free(ptr);
	return (NULL);
}

t_token_manager	*prompt(t_env_manager *env_manager)
{
	char		*line;
	t_token_manager	*tokenized;
	t_string	buffer;
    t_string    expanded;

	if (init_string(&buffer, DEFAULT_INIT_SIZE) == NULL)
		return (NULL);
    signal_info.status = READING_PROMPT;
	line = readline("minishell$ ");
    signal_info.status = UNDEFINED;
	if (line == NULL)
	{
		free(buffer.data);
		return NULL;
	}
	if (push_back_string(&buffer, line) == NULL)
		free_with_return_null(line);
	printf("'%s'\n", buffer.data);
	add_history(buffer.data);
    if (expand_env(&expanded, &buffer, env_manager) == NULL) {
        // TODO: error handring
    }
	tokenized = tokenize(&expanded, env_manager);
	free(line);
	free(buffer.data);
    free(expanded.data);
	return (tokenized);
}
