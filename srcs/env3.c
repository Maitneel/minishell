/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:21:24 by dummy             #+#    #+#             */
/*   Updated: 2023/07/09 17:19:38 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ft_xcalloc.h"
#include "command_exec.h"
#include "env.h"

char	**make_env_ptr(t_env_manager *env_manager)
{
	char	**env_ptr;
	t_env	*current;
	size_t	i;

	env_ptr = ft_xcalloc(sizeof(char *), env_manager->size + 1);
	if (env_ptr == NULL)
		return (NULL);
	i = 0;
	current = env_manager->front;
	while (i < env_manager->size)
	{
		env_ptr[i] = get_raw_string(current);
		if (env_ptr[i] == NULL)
			return (free_string_array(env_ptr));
		current = current->next;
		i++;
	}
	return (env_ptr);
}
