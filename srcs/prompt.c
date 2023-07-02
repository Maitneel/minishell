/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:27:47 by dummy             #+#    #+#             */
/*   Updated: 2023/07/02 20:50:07 by dummy            ###   ########.fr       */
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

char	ft_is_space(char c)
{
	if (c == ' ' )
		return true;
	if (c == '\t' )
		return true;
	if (c == '\n' )
		return true;
	if (c == '\v' )
		return true;
	if (c == '\f' )
		return true;
	if (c == '\r')
		return true;
	return false;
}

bool	is_empty_string(char *str)
{
	size_t i ;

	i = 0 ;
	while (str[i] != '\0')
	{
		if (!ft_is_space(str[i]))
		{
			return false;
		}
		i++;
	}
	return true;
}

char	*read_prompt(void)
{
	char	*line;

	line = NULL;
	while (line == NULL)
	{
		g_signal_info.status = READING_PROMPT;
		line = readline("minishell$ ");
		g_signal_info.status = UNDEFINED;
		if (line == NULL)
			break ;
		if (is_empty_string(line))
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
		perror("minishell");
		return (NULL);
	}
	tokenized = tokenize(&expanded, env_manager);
	free(buffer.data);
	free(expanded.data);
	return (tokenized);
}
