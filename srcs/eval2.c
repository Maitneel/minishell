/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:29:36 by dummy             #+#    #+#             */
/*   Updated: 2023/07/08 13:33:00 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdbool.h"
#include "tokenize.h"
#include "libft.h"

bool	should_eval(t_token *token)
{
	const char		*eval_char = "'\"$\\";
	const size_t	eval_char_size = 4;
	size_t			i;
	size_t			j;

	i = 0;
	while (token->word[i] != '\0')
	{
		j = 0;
		while (j < eval_char_size)
		{
			if (token->word[i] == eval_char[j])
			{
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

bool	is_env_delimiter(char c)
{
	return (!(ft_isalnum(c) || c == '_'));
}

bool	is_change_quote_flag(char quote_flag, char current_char)
{
	if (!(current_char == '\'' || current_char == '"'))
		return (false);
	if (current_char != quote_flag && quote_flag != '\0')
		return (false);
	return (true);
}

bool	is_expand(char quote_flag)
{
	return (quote_flag == '\0' || quote_flag == '"');
}

bool	is_add_doller(char *string)
{
	return (string[0] == '$' && is_env_delimiter(string[1]));
}
