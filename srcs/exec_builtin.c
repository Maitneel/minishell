/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:25:27 by taksaito          #+#    #+#             */
/*   Updated: 2023/06/25 19:35:39 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "builtin.h"

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
		NULL};

	i = 0;
	while (commands[i])
	{
		if (ft_strcmp((char *)commands[i], command) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	exec_builtin(t_command *command, char **args, t_env_manager *env_manager)
{
	if (ft_strcmp(command->command_name, "echo") == 0)
		return (command_echo(args));
	if (ft_strcmp(command->command_name, "cd") == 0)
		return (command_cd(args));
	if (ft_strcmp(command->command_name, "pwd") == 0)
		return (command_pwd());
	if (ft_strcmp(command->command_name, "env") == 0)
		return (command_env(env_manager, args));
	if (ft_strcmp(command->command_name, "export") == 0)
		return (command_export(env_manager, args));
	if (ft_strcmp(command->command_name, "unset") == 0)
		return (command_unset(env_manager, args));
	if (ft_strcmp(command->command_name, "exit") == 0)
		return (command_exit(env_manager, args));
	return (0);
}
