/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:27:47 by dummy             #+#    #+#             */
/*   Updated: 2023/06/25 21:01:25 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include <readline/history.h>
#include <readline/readline.h>

#include "ft_string.h"
#include "tokenize.h"
#include "expand_env.h"
#include "ft_signal.h"

// static void	*free_with_return_null(void *ptr)
// {
// 	free(ptr);
// 	return (NULL);
// }

char	*read_prompt(void)
{
	char	*line;

	line = NULL;
	while (line == NULL)
	{
		g_signal_info.status = READING_PROMPT;
		line = readline("minishe$ ");
		g_signal_info.status = UNDEFINED;
		if (line == NULL)
			break ;
		if (line[0] == '\0')
		{
			free(line);
			line = NULL;
		}
	}
	return (line);
}

t_token_manager	*prompt(t_env_manager *env_manager)
{
	t_token_manager	*tokenized;
	t_string		buffer;
	t_string		expanded;

	buffer.data = NULL;
	while (buffer.data == NULL)
	{
		if (set_string(&buffer, read_prompt()) == NULL)
		{
			g_signal_info.status = UNDEFINED;
			write(STDOUT_FILENO, "exit\n", 5);
			return (NULL);
		}
	}
	add_history(buffer.data);
	if (expand_env(&expanded, &buffer, env_manager) == NULL)
	{
		free(buffer.data);
		// TODO: error handring
		// エラー(mallocの失敗とか)をどうするかという処理
		return (NULL);
	}
	tokenized = tokenize(&expanded, env_manager);
	free(buffer.data);
	free(expanded.data);
	return (tokenized);
}
