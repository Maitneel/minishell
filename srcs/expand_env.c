/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:02:11 by dummy             #+#    #+#             */
/*   Updated: 2023/07/21 16:38:36 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_string.h"
#include "ft_xcalloc.h"
#include "tokenize.h"
#include "expand_env.h"
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

bool	is_env_key_char(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

t_string	*expnad_env_helper(t_string *expanded, t_string *line,
					char quote_flag, t_env_manager *env_manager)
{
	char	*expanded_pipe;
	size_t	i;

	i = 0;
	while (line->data[i] != '\0')
	{
		quote_check(line->data, &quote_flag, &i);
		if (line->data[i] == '$' && quote_flag != '\'' && \
			is_env_key_char(line->data[i + 1]))
		{
			expanded_pipe = get_expande_pipe(get_env_value_ptr(&line->data[i
						+ 1], &i, env_manager), true, quote_flag);
			if (push_back_string(expanded, expanded_pipe) == NULL)
				return (NULL);
			free(expanded_pipe);
		}
		else
		{
			if (push_back_string_char(expanded, line->data[i]) == NULL)
				return (NULL);
		}
		i++;
	}
	return (expanded);
}

t_string	*expand_env(t_string *expanded, t_string *line,
		t_env_manager *env_manager)
{
	char	quote_flag;

	quote_flag = '\0';
	if (line == NULL || env_manager == NULL)
		return (NULL);
	if (init_string(expanded, DEFAULT_INIT_SIZE) == NULL)
		return (NULL);
	return (expnad_env_helper(expanded, line, quote_flag, env_manager));
}
