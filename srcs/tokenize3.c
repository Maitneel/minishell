/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:26:22 by dummy             #+#    #+#             */
/*   Updated: 2023/07/17 17:15:00 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include <stdbool.h>
#include <stddef.h>

bool	is_delimiter(char c)
{
	const char		*delimiter = " \t\n\f\r";
	const size_t	delimiter_size = 5;
	size_t			i;

	i = 0;
	while (i < delimiter_size)
	{
		if (c == delimiter[i])
		{
			return (true);
		}
		i++;
	}
	return (false);
}

bool	is_meta_char(char c)
{
	const char		*meta_char = "<>|";
	const size_t	meta_char_size = 4;
	size_t			i;

	i = 0;
	while (i < meta_char_size)
	{
		if (c == meta_char[i])
		{
			return (true);
		}
		i++;
	}
	return (false);
}

void	quote_check(char *line, char *quote, size_t *i)
{
	if ((line[*i] == '\'' || line[*i] == '"'))
	{
		if (*quote == '\0')
			*quote = line[*i];
		else if (*quote == line[*i])
			*quote = '\0';
	}
}

size_t	set_next_char(char *line, char *token_string, char *quote, size_t *i)
{
	size_t	index;

	index = 0;
	if (!is_delimiter(line[*i]) || *quote != '\0')
	{
		token_string[index] = line[*i];
		(index)++;
		if (is_meta_char(line[*i]) && line[*i] == line[*i + 1]
			&& line[*i] != '|')
		{
			(*i)++;
			token_string[index] = line[*i];
			(index)++;
		}
	}
	return (index);
}

size_t	set_next_token_string(char *token_string, char *line)
{
	char	quote;
	size_t	i;
	size_t	str_index;
	size_t	line_length;

	quote = '\0';
	i = 0;
	str_index = 0;
	line_length = ft_strlen(line);
	while (i < line_length)
	{
		quote_check(line, &quote, &i);
		str_index += set_next_char(line, &token_string[str_index], &quote, &i);
		if (((str_index != 0 && ft_strlen(token_string) != 0
					&& (is_delimiter(line[i + 1]) || is_meta_char(line[i + 1])
						|| is_meta_char(line[i]))) && quote == '\0')
			|| i == line_length - 1)
		{
			break ;
		}
		i++;
	}
	return (i + 1);
}
