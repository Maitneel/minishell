/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:26:16 by dummy             #+#    #+#             */
/*   Updated: 2023/07/03 21:38:04 by taksaito         ###   ########.fr       */
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
# include "ft_xsplit.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int		command_exec(t_command *commands, t_env_manager *env_manager);
void	unlink_tempfile(t_command *command);
void	*free_string_array(char **string_array);
char	*generate_no_exist_file_name(char *front_string);
char	**make_args(t_command *command);
bool	is_builtin(char *command);
void	*free_string_array(char **string_array);
size_t	get_args_list_size(t_command *command);
char	*expand_line(char *line, t_env_manager *env_manager);
int		expand_and_write(int fd, t_redirect_info *info,
			t_env_manager *env_manager);
char	*here_doc(t_redirect_info *info, t_env_manager *env_manager);
char	**make_args(t_command *command);
char	*make_path(const char *path, const char *command);
char	*find_path(t_command *command, t_env_manager *env_manager);
int		exec_builtin(t_command *command, char **args,
			t_env_manager *env_manager, int output_fd);
int		ft_exec(t_command *command, t_env_manager *env_manager);
int		files_create(t_redirect_info *outputs);
int		files_dup2_stdin(t_redirect_info *inputs);
int		pipe_exec(int before_fd, t_command *command,
			t_env_manager *env_manager);
int		non_pipe_exec(int before_fd, t_command *command,
			t_env_manager *env_manager);
void	non_pipe_child_exec(int before_fd, t_command *command,
			t_env_manager *env_manager);
void	pipe_child_exec(int before_fd, int pipe_fd[2], t_command *command,
			t_env_manager *env_manager);

#endif