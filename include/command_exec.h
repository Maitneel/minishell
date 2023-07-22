/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:26:16 by dummy             #+#    #+#             */
/*   Updated: 2023/07/22 18:12:00 by dummy            ###   ########.fr       */
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

# include <stdlib.h>

# include <unistd.h>

int		command_exec(t_command *commands, t_env_manager *env_manager);
void	unlink_tempfile(t_command *command);
void	wait_child_proceess(t_pid_list *pid_list, t_env_manager *env_manager);
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
			t_pid_list **pid_list, t_env_manager *env_manager);
int		non_pipe_exec(int before_fd, t_command *command,
			t_pid_list **pid_list, t_env_manager *env_manager);
void	non_pipe_child_exec(int before_fd, t_command *command,
			t_env_manager *env_manager);
void	pipe_child_exec(int before_fd, int pipe_fd[2], t_command *command,
			t_env_manager *env_manager);
int		can_open_input_files(t_redirect_info *input_current,
			t_env_manager *env_manager);
bool	is_path(char *str);
void	exec_end_processing(t_pid_list *pid_list, t_command *command,
			t_env_manager *env_manager);
void	heredoc_child(char *file_name, t_redirect_info *info,
			t_env_manager *env_manager);
#endif