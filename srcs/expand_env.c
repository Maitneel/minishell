/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:02:11 by dummy             #+#    #+#             */
/*   Updated: 2023/06/18 20:30:29 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "string.h"
#include "tokenize.h"
#include <stdio.h>
#include <stdlib.h>

void	expand_env_setup(char *quote_flag, size_t *i)
{
	(*i) = -1;
	*quote_flag = '\0';
}

t_string	*push_back_string_char(t_string *string, char c)
{
	char	temp[2];

	temp[0] = c;
	temp[1] = '\0';
	return (push_back_string(string, temp));
}

t_string	*expand_env(t_string *expanded, t_string *line,
		t_env_manager *env_manager)
{
	char	quote_flag;
	size_t	i;

	expand_env_setup(&quote_flag, &i);
	if (line == NULL || env_manager == NULL)
		return (NULL);
	if (init_string(expanded, DEFAULT_INIT_SIZE) == NULL)
		return (NULL);
	while (line->data[++i] != '\0')
	{
		quote_check(line->data, &quote_flag, &i);
		if (line->data[i] == '$' && quote_flag != '\'')
		{
			if (push_back_string(expanded, get_env_value_ptr(&line->data[i + 1],
						&i, env_manager)) == NULL)
				return (NULL);
		}
		else
		{
			if (push_back_string_char(expanded, line->data[i]) == NULL)
				return (NULL);
		}
	}
	return (expanded);
}
