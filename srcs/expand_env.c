/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:02:11 by dummy             #+#    #+#             */
/*   Updated: 2023/06/11 16:36:59 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "string.h"
#include "tokenize.h"
#include <stdio.h>
#include <stdlib.h>

t_string	*expand_env(t_string *expanded, t_string *line, t_env_manager *env_manager)
{
	char temp[2];
    char quote_flag;

    quote_flag = '\0';
	temp[1] = '\0';
	if (line == NULL || env_manager == NULL)
		return (NULL);
	if (init_string(expanded, DEFAULT_INIT_SIZE) == NULL)
		return (NULL);
	size_t i;
	i = 0;
	while (line->data[i] != '\0')
	{
        if ((line->data[i] == '"' || line->data[i] == '\'') && (quote_flag == '\0' || quote_flag == line->data[i]))
            quote_flag ^= line->data[i];
		if (line->data[i] == '$' && quote_flag != '\'')
		{
			if (push_back_string(expanded, get_env_value_ptr(&line->data[i + 1], &i, env_manager)) == NULL)
				return (NULL);
		}
		else
		{
			temp[0] = line->data[i];
			if (push_back_string(expanded, temp) == NULL)
				return (NULL);
		}
		i++;
	}
	printf("expanded->data : '%s'\n", expanded->data);
	return (expanded);
}