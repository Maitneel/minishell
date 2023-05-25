/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:27:47 by dummy             #+#    #+#             */
/*   Updated: 2023/05/25 15:46:48 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "tokenize.h"
#include <errno.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdlib.h>

static bool	is_input_end(char *line, char *quote)
{
	size_t	i;

	if (line == NULL && *quote == '\0')
		return (true);
	if (line == NULL && *quote != '\0')
		return (false);
	i = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == '\'' || line[i] == '"'))
		{
			if (*quote == line[i])
				*quote = '\0';
			else if (*quote == '\0')
				*quote = line[i];
		}
		i++;
	}
	if (*quote == '\'' || *quote == '"')
		return (false);
	else
		return (true);
}

static void	*free_with_return_null(void *ptr)
{
	free(ptr);
	return (NULL);
}

t_token_manager	*prompt(t_env_manager *env_manager)
{
	char		*line;
	char		quote;
	t_token_manager	*tokenized;
	t_string	buffer;

	quote = '\0';
	if (init_string(&buffer, DEFAULT_INIT_SIZE) == NULL)
		return (NULL);
	line = readline("minishell$ ");
	while (!is_input_end(line, &quote))
	{
		if (push_back_string(&buffer, line) == NULL)
			free_with_return_null(line);
		if (push_back_string(&buffer, "\n") == NULL)
			free_with_return_null(line);
		free(line);
		line = readline("> ");
	}
	if (push_back_string(&buffer, line) == NULL)
		free_with_return_null(line);
	printf("%s\n", buffer.data);
	add_history(buffer.data);
	tokenized = tokenize(&buffer, env_manager);
	free(line);
	free(buffer.data);
	return (tokenized);
}
