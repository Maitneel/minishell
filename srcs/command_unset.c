/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:35:45 by taksaito          #+#    #+#             */
/*   Updated: 2023/06/25 17:01:37 by taksaito         ###   ########.fr       */
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
		write(STDERR_FILENO, "unset: not enough arguments\n", 28);
		return (1);
	}
	i = 1;
	while (i < tokens_size)
	{
		env_delete(env_manager, tokens[i]);
		i++;
	}
	return (0);
}
