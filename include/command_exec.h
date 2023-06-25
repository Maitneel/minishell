/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 16:26:16 by dummy             #+#    #+#             */
/*   Updated: 2023/06/25 16:26:17 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_EXEC_H
# define COMMAND_EXEC_H

# include "env.h"
# include "parser.h"

int		command_exec(t_command *commands, t_env_manager *env_manager);
void	*free_string_array(char **string_array);
char	*generate_no_exist_file_name(char *front_string);
char	**make_args(t_command *command);

#endif