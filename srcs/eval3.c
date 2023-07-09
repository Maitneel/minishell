/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:34:13 by dummy             #+#    #+#             */
/*   Updated: 2023/07/09 16:22:45 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stddef.h>
#include "libft.h"
#include "tokenize.h"

char	*get_env_value_ptr(char *token_string, size_t *token_index,
		t_env_manager *env_manager)
{
	char	*key;
	size_t	i;
	t_env	*env;

	if (token_string == NULL || env_manager == NULL)
		return (NULL);
	i = 0;
	(*token_index)++;
	if ((ft_isdigit(token_string[0]) || (token_string[0] == '?')))
		return (get_special_env(token_string[0], env_manager));
	else
	{
		key = ft_strdup(token_string);
		if (key == NULL)
			return (NULL);
		while (!is_env_delimiter(key[i]))
			i++;
	}
	key[i] = '\0';
	*token_index += i - 1;
	env = find_env(env_manager, key);
	free(key);
	if (env == NULL)
		return (NULL);
	return (env->value);
}
