/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 18:56:53 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/09 16:06:24 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"

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
	char	*end_text;

	end_text = ft_strjoin(info->arg, "\n");
	if (end_text == NULL)
		return (-1);
	while (true)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(g_signal_info.heredoc_fd);
		if (line == NULL)
			break ;
		if (strcmp(line, end_text) == 0)
			break ;
		expanded = expand_line(line, env_manager);
		free(line);
		if (expanded == NULL)
			return (-1);
		write(fd, expanded, ft_strlen(expanded));
		free(expanded);
	}
	free(line);
	free(end_text);
	return (fd);
}
