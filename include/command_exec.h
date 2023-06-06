#ifndef COMMAND_EXEC_H
# define COMMAND_EXEC_H

# include "parser.h"
# include "env.h"

int	command_exec(t_command *commands, t_env_manager *env_manager);
void *free_string_array(char **string_array);

#endif