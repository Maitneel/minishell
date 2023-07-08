/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 06:58:37 by dummy             #+#    #+#             */
/*   Updated: 2023/07/03 19:20:21 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "env.h"
#include "parser.h"
#include <unistd.h>

int	set_heredoc_error(t_command *command, t_env_manager *env_manager)
{
	g_signal_info.resived_sigid = -1;
	env_manager->exit_status = 1;
	command->is_heredoc_error = true;
	// ここは挙動として正しいエラーなので0を返す(他の値でもいい)
	return (0);
}

int	processing_heredoc(t_redirect_info *current, t_env_manager *env_manager)
{
	char	*file_name;

	g_signal_info.heredoc_fd = dup(STDIN_FILENO);
	if (g_signal_info.heredoc_fd == -1)
	{
		// TODO errorhandring
		// ここはできなければexitでいい気がする
	}
	g_signal_info.status = READING_HEREDOC;
	file_name = here_doc(current, env_manager);
	g_signal_info.status = UNDEFINED;
	close(g_signal_info.heredoc_fd);
	g_signal_info.heredoc_fd = -1;
	if (file_name == NULL)
		return (-1);
	free(current->arg);
	current->arg = file_name;
	current->kind = EXPANDED_HEREDOC;
	return (0);
}

int	expand_here_of_one_command(t_command *command, t_env_manager *env_manager)
{
	t_redirect_info	*current;

	current = command->inputs;
	while (current != NULL)
	{
		if (current->kind == REDIRECT_HEAR_DOC)
		{
			if (processing_heredoc(current, env_manager) == -1)
			{
				// error handring
			}
			if (g_signal_info.resived_sigid == SIGINT)
				return (set_heredoc_error(command, env_manager));
		}
		current = current->next;
	}
	return (0);
}

int	expand_here_doc(t_command *command, t_env_manager *env_manager)
{
	t_command	*current_command;

	if (command == NULL)
		return (-2);
	current_command = command;
	while (current_command != NULL)
	{
		if (expand_here_of_one_command(current_command, env_manager) != 0)
		{
			// TODO error handring
			// heredocが失敗した時にどういう処理をするか
			// 今までは小プロセスで実行していたが、ここでは親プロセスでの実行になるので
			// 安易にexitしていいのか
		}
		if (current_command->is_heredoc_error == true)
		{
			unlink_tempfile(command);
			command->is_heredoc_error = true;
			return (-1);
		}
		current_command = current_command->next;
	}
	return (0);
}
