/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:27:47 by dummy             #+#    #+#             */
/*   Updated: 2023/05/14 16:13:08 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

t_tokenize *prompt(void)
{
	char *line;
	t_tokenize *tokenized;

	line = readline("minishell$ ");
	printf("%s\n", line);	
	add_history(line);
	tokenized = tokenize(line);

	return tokenized;
}
