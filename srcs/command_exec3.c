/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:42:10 by taksaito          #+#    #+#             */
/*   Updated: 2023/07/22 18:11:28 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "signal_handler.h"
#include <stdio.h>
#include <sys/wait.h>

char	*here_doc(t_redirect_info *info, t_env_manager *env_manager)
{
	char	*file_name;
	pid_t	pid;
	int		exit_code;

	file_name = generate_no_exist_file_name("/tmp/here_doc_tmp");
	if (file_name == NULL)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
	{
		heredoc_child(file_name, info, env_manager);
	}
	wait(&exit_code);
	if (exit_code != 0)
		return (NULL);
	return (file_name);
}

char	**make_args(t_command *command)
{
	size_t		args_size;
	char		**args_array;
	t_args_list	*args_list;
	size_t		i;

	args_size = get_args_list_size(command) + 1;
	args_array = ft_xcalloc(args_size + 1, sizeof(char *));
	if (args_array == NULL)
		return (NULL);
	args_array[0] = ft_strdup(command->command_name);
	if (args_array[0] == NULL)
		return (free_string_array(args_array));
	i = 1;
	args_list = command->args_list;
	while (args_list != NULL)
	{
		args_array[i] = ft_strdup(args_list->string);
		if (args_array[i] == NULL)
			return (free_string_array(args_array));
		i++;
		args_list = args_list->next;
	}
	return (args_array);
}

char	*make_path(const char *path, const char *command_name)
{
	char	*slashed;
	char	*joined;

	if (path == NULL || command_name == NULL)
		exit(1);
	slashed = ft_strjoin(path, "/");
	if (slashed == NULL)
		ft_exit(ALOCATE_ERROR);
	joined = ft_strjoin(slashed, command_name);
	free(slashed);
	if (joined == NULL)
		ft_exit(ALOCATE_ERROR);
	return (joined);
}

char	*find_path(t_command *cmd, t_env_manager *env_manager)
{
	t_env	*path_env;
	size_t	i;
	char	*absolute_path;
	char	**paths;

	if (access(cmd->command_name, F_OK) == 0 && is_path(cmd->command_name))
		return (ft_strdup(cmd->command_name));
	path_env = find_env(env_manager, "PATH");
	if (path_env == NULL)
		return (NULL);
	paths = ft_xsplit(path_env->value, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		absolute_path = make_path(paths[i], cmd->command_name);
		if (access(absolute_path, F_OK) == 0)
		{
			free_string_array(paths);
			return (absolute_path);
		}
		free(absolute_path);
		i++;
	}
	return (free_string_array(paths));
}

int	exec_builtin(t_command *command, char **args, t_env_manager *env_manager,
		int output_fd)
{
	if (ft_strcmp(command->command_name, "echo") == 0)
		return (command_echo(args, output_fd));
	if (ft_strcmp(command->command_name, "cd") == 0)
		return (command_cd(env_manager, args));
	if (ft_strcmp(command->command_name, "pwd") == 0)
		return (command_pwd(output_fd));
	if (ft_strcmp(command->command_name, "env") == 0)
		return (command_env(env_manager, args, output_fd));
	if (ft_strcmp(command->command_name, "export") == 0)
		return (command_export(env_manager, args));
	if (ft_strcmp(command->command_name, "unset") == 0)
		return (command_unset(env_manager, args));
	if (ft_strcmp(command->command_name, "exit") == 0)
		return (command_exit(env_manager, args));
	return (0);
}
