/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:27:47 by dummy             #+#    #+#             */
/*   Updated: 2023/05/17 04:51:57 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "tokenize.h"
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

bool	is_input_end(char *line, char *quote)
{
	size_t	i;

	if (line == NULL && *quote == '\0')
		return true;
	i = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == '`' || line[i] == '"'))
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

t_tokenize	*prompt(void)
{
	char		*line;
	// char		quote;
	t_tokenize	*tokenized;
	// t_string	buffer;

	// quote = '\0';
	// if (init_string(&buffer, DEFAULT_INIT_SIZE))
	// 	return (NULL);
	line = readline("minishell$ ");
	// while (!is_input_end(line, &quote))
	// {
	// 	if (push_back_string(&buffer, line) == NULL);
	// 	{
	// 		free(line);
	// 		return NULL;
	// 	}
	// 	line = readline("> ");
	// 	if (line == NULL)
	// 	{
	// 		printf("minishell: %s", strerror(errno));
	// 		return NULL;
	// 	}
		
	// }
	
	printf("%s\n", line);
	add_history(line);
	tokenized = tokenize(line);
	return (tokenized);
}
