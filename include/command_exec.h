/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:26:16 by dummy             #+#    #+#             */
/*   Updated: 2023/07/01 19:00:24 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_EXEC_H
# define COMMAND_EXEC_H

# define WRITE_FD 1
# define READ_FD 0

# include "env.h"
# include "parser.h"
# include "builtin.h"
# include "env.h"
# include "expand_env.h"
# include "ft_signal.h"
# include "get_next_line.h"
# include "libft.h"
# include "ft_xcalloc.h"
# include "parser.h"
# include "tokenize.h"
# include "print_lib.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int		command_exec(t_command *commands, t_env_manager *env_manager);
void	*free_string_array(char **string_array);
char	*generate_no_exist_file_name(char *front_string);
char	**make_args(t_command *command);
bool	is_builtin(char *command);
void	*free_string_array(char **string_array);
size_t	get_args_list_size(t_command *command);
char	*expand_line(char *line, t_env_manager *env_manager);
int		expand_and_write(int fd, t_redirect_info *info,
			t_env_manager *env_manager);

#endif