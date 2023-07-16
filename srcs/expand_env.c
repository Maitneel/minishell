/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:02:11 by dummy             #+#    #+#             */
/*   Updated: 2023/07/16 20:44:26 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "ft_string.h"
#include "ft_xcalloc.h"
#include "tokenize.h"
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

int	puhs_back_expand_pipe(t_string *expanded, t_string *line, size_t *i,
		t_env_manager *env_manager)
{
	if (push_back_string(expanded, get_env_value_ptr(&line->data[*i + 1], i,
				env_manager)) == NULL)
		return (1);
	return (0);
}

size_t	get_number_of_include_pipe(char *str)
{
	size_t	result;
	size_t	i;

	result = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
			result++;
		i++;
	}
	return (result);
}

#include <stdio.h>

void	expand_pipe(char **dest, char *env_ptr, char quote_flag, size_t length)
{
	size_t	i;

	i = 0;
	while (*env_ptr != '\0' && i < length)
	{
		if (*env_ptr == '|')
		{
			if (quote_flag != '\0')
				(*dest)[i++] = quote_flag;
			(*dest)[i + 0] = '"';
			(*dest)[i + 1] = '|';
			(*dest)[i + 2] = '"';
			i += 3;
			if (quote_flag != '\0')
				(*dest)[i++] = quote_flag;
		}
		else
		{
			(*dest)[i] = *env_ptr;
			i++;
		}
		env_ptr++;
	}
}

char	*get_expande_pipe(char *env_ptr, bool is_expand, char quote_flag)
{
	char	*expanded;
	size_t	length;

	if (env_ptr == NULL)
		return (NULL);
	if (is_expand == false)
	{
		expanded = ft_strdup(env_ptr);
		if (expanded == NULL)
		{
			write(STDERR_FILENO, "minishell: failed to allocate memory\n", 38);
			exit(1);
		}
		return (expanded);
	}
	length = ft_strlen(env_ptr) + get_number_of_include_pipe(env_ptr) * 2 + 1;
	if (quote_flag != '\0')
		length += get_number_of_include_pipe(env_ptr) * 2;
	expanded = ft_xcalloc(sizeof(char), length);
	expand_pipe(&expanded, env_ptr, quote_flag, length);
	return (expanded);
}

t_string	*expand_env(t_string *expanded, t_string *line,
		t_env_manager *env_manager)
{
	char	quote_flag;
	size_t	i;
	char	*expanded_pipe;

	expand_env_setup(&quote_flag, &i);
	if (line == NULL || env_manager == NULL)
		return (NULL);
	if (init_string(expanded, DEFAULT_INIT_SIZE) == NULL)
		return (NULL);
	while (line->data[++i] != '\0')
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
	}
	return (expanded);
}
