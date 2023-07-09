/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:35:45 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/09 20:40:00 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	command_unset(t_env_manager *env_manager, char **tokens)
{
	int	tokens_size;
	int	i;

	tokens_size = array_size(tokens);
	if (tokens_size == 1)
	{
		return (0);
	}
	i = 1;
	while (i < tokens_size)
	{
		env_delete(env_manager, tokens[i]);
		i++;
	}
	return (0);
}
