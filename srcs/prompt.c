/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:27:47 by dummy             #+#    #+#             */
/*   Updated: 2023/07/22 17:31:21 by dummy            ###   ########.fr       */
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
#include "signal_handler.h"

char	ft_is_space(char c)
{
	if (c == ' ')
		return (true);
	if (c == '\t')
		return (true);
	if (c == '\n')
		return (true);
	if (c == '\v')
		return (true);
	if (c == '\f')
		return (true);
	if (c == '\r')
		return (true);
	return (false);
}

bool	is_empty_string(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_is_space(str[i]))
		{
			return (false);
		}
		i++;
	}
	return (true);
}

char	*read_prompt(t_env_manager *env_manager)
{
	char	*line;

	line = NULL;
	while (line == NULL)
	{
		register_signal_handler(readline_signal_handler);
		line = readline("minishell$ ");
		if (g_recived_signal_id == SIGINT)
		{
			env_manager->exit_status = 1;
			g_recived_signal_id = -1;
		}
		register_signal_handler(signal_handler);
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
		if (set_string(&buffer, read_prompt(env_manager)) == NULL)
		{
			write(STDERR_FILENO, "exit\n", 5);
			return (NULL);
		}
	}
	add_history(buffer.data);
	if (expand_env(&expanded, &buffer, env_manager) == NULL)
	{
		free(buffer.data);
		perror("minishell");
		return (NULL);
	}
	tokenized = tokenize(&expanded, env_manager);
	free(buffer.data);
	free(expanded.data);
	return (tokenized);
}
