/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 20:58:23 by taksaito          #+#    #+#             */
/*   Updated: 2023/06/25 21:03:28 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"

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

char	**make_args(t_command *command)
{
	size_t		args_size;
	char		**args_array;
	t_args_list	*args_list;
	size_t		i;

	args_size = get_args_list_size(command) + 1;
	args_array = calloc(args_size + 1, sizeof(char *));
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

char	*make_path(const char *path, const char *command)
{
	char	*slashed;
	char	*joined;

	if (path == NULL || command == NULL)
		return (NULL);
	slashed = ft_strjoin(path, "/");
	if (slashed == NULL)
		return (NULL);
	joined = ft_strjoin(slashed, command);
	free(slashed);
	return (joined);
}

char	*find_path(t_command *command, t_env_manager *env_manager)
{
	t_env	*path_env;
	size_t	i;
	char	*absolute_path;
	char	**paths;

	if (access(command->command_name, F_OK) == 0)
		return (ft_strdup(command->command_name));
	path_env = find_env(env_manager, "PATH");
	if (path_env == NULL)
		return (NULL);
	paths = ft_split(path_env->value, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		absolute_path = make_path(paths[i], command->command_name);
		if (absolute_path == NULL)
			return (free_string_array(paths));
		if (access(absolute_path, F_OK) == 0)
		{
			free_string_array(paths);
			return (absolute_path);
		}
		free(absolute_path);
		i++;
	}
	free_string_array(paths);
	return (NULL);
}
