/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:20:07 by dummy             #+#    #+#             */
/*   Updated: 2023/07/22 18:26:57 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_exec.h"
#include "signal_handler.h"

void	heredoc_child(char *file_name, t_redirect_info *info,
		t_env_manager *env_manager)
{
	int	output_fd;

	register_signal_handler(heredoc_child_signal_handler);
	output_fd = open(file_name, (O_WRONLY | O_CREAT), 0644);
	if (output_fd == -1)
	{
		free(file_name);
		exit(1);
	}
	if (expand_and_write(output_fd, info, env_manager) == -1)
	{
		unlink(file_name);
		exit(1);
	}
	exit(0);
}
