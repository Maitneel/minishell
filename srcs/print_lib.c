/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:21:03 by dummy             #+#    #+#             */
/*   Updated: 2023/07/09 16:07:52 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "tokenize.h"
#include <unistd.h>

void	put_command_not_found(char *command)
{
	write(STDERR_FILENO, "minishell: ", 12);
	write(STDERR_FILENO, command, ft_strlen(command));
	write(STDERR_FILENO, ": command not found\n", 21);
}

void	print_unclosed_quote(void)
{
	write(STDERR_FILENO, "minishell: syntax error unclosed quote\n", 40);
}

void	print_syntax_error(t_token *token)
{
	write(STDERR_FILENO, "minishell: syntax error near unexpected token `", 47);
	if (token == NULL)
		write(STDERR_FILENO, "newline", 7);
	else
		write(STDERR_FILENO, token->word, ft_strlen(token->word));
	write(STDERR_FILENO, "'\n", 2);
}
