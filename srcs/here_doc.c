/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:35:47 by taksaito          #+#    #+#             */
/*   Updated: 2023/06/25 19:44:59 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "expand_env.h"
#include "libft.h"
#include "get_next_line.h"
#include "builtin.h"
#include <fcntl.h>

int	here_doc(t_redirect_info *info, t_env_manager *env_manager)
{
	int		output_fd;
	int		input_fd;
	char	*file_name;

	file_name = generate_no_exist_file_name("/tmp/here_doc_tmp");
	if (file_name == NULL)
		return (-1);
	output_fd = open(file_name, (O_WRONLY | O_CREAT));
	if (output_fd == -1)
	{
		free(file_name);
		return (-1);
	}
	input_fd = open(file_name, (O_RDONLY));
	unlink(file_name);
	free(file_name);
	if (input_fd == -1)
	{
		close(output_fd);
		return (-1);
	}
	if (expand_and_write(output_fd, info, env_manager) == -1)
		return (-1);
	return (input_fd);
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
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			break ;
		if (ft_strcmp(line, end_text) == 0)
			break ;
		expanded = expand_line(line, env_manager);
		free(line);
		if (expanded == NULL)
			return (-1);
		if (write(fd, expanded, ft_strlen(expanded)) == -1)
		{
			free(expanded);
			return (-1);
		}
		free(expanded);
	}
	free(line);
	free(end_text);
	return (fd);
}
