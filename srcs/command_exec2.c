/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 18:56:53 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/22 18:00:29 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include <stdio.h>
#include <readline/readline.h>

bool	is_builtin(char *command)
{
	size_t		i;
	const char	*commands[] = {
		"echo",
		"export",
		"pwd",
		"cd",
		"echo",
		"pwd",
		"unset",
		"exit",
		"env",
		NULL
	};

	if (command == NULL)
		return (false);
	i = 0;
	while (commands[i])
	{
		if (ft_strcmp((char *)commands[i], command) == 0)
			return (true);
		i++;
	}
	return (false);
}

void	*free_string_array(char **string_array)
{
	size_t	i;

	i = 0;
	while (string_array[i] != NULL)
	{
		free(string_array[i]);
		i++;
	}
	free(string_array);
	return (NULL);
}

size_t	get_args_list_size(t_command *command)
{
	size_t		size;
	t_args_list	*args_list;

	args_list = command->args_list;
	size = 0;
	while (args_list != NULL)
	{
		args_list = args_list->next;
		size++;
	}
	return (size);
}

char	*expand_line(char *line, t_env_manager *env_manager)
{
	t_string	struct_line;
	t_string	expanded;

	struct_line.data = line;
	struct_line.length = ft_strlen(line);
	struct_line.max_length = struct_line.length;
	if (expand_env(&expanded, &struct_line, env_manager) == NULL)
		return (NULL);
	return (expanded.data);
}

int	expand_and_write(int fd, t_redirect_info *info, t_env_manager *env_manager)
{
	char	*line;
	char	*expanded;

	while (true)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, info->arg) == 0)
			break ;
		expanded = expand_line(line, env_manager);
		free(line);
		if (expanded == NULL)
			return (-1);
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
	}
	free(line);
	return (fd);
}
