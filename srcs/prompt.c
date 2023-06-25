/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:27:47 by dummy             #+#    #+#             */
/*   Updated: 2023/06/25 16:27:55 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include <readline/history.h>
#include <readline/readline.h>

#include "ft_string.h"
#include "tokenize.h"
#include "expand_env.h"
#include "ft_signal.h"

// static void	*free_with_return_null(void *ptr)
// {
// 	free(ptr);
// 	return (NULL);
// }

t_token_manager	*prompt(t_env_manager *env_manager)
{
	t_token_manager	*tokenized;
	t_string		buffer;
	t_string		expanded;

	g_signal_info.status = READING_PROMPT;
	if (set_string(&buffer, readline("minishell$ ")) == NULL)
	{
		g_signal_info.status = UNDEFINED;
		write(STDOUT_FILENO, "exit\n", 5);
		return (NULL);
	}
	g_signal_info.status = UNDEFINED;
	add_history(buffer.data);
	if (expand_env(&expanded, &buffer, env_manager) == NULL)
	{
		free(buffer.data);
		// TODO: error handring
		// エラー(mallocの失敗とか)をどうするかという処理
		return (NULL);
	}
	tokenized = tokenize(&expanded, env_manager);
	free(buffer.data);
	free(expanded.data);
	return (tokenized);
}
