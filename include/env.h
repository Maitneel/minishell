#ifndef ENV_H
# define ENV_H

#include <stddef.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_env_manager
{
	struct s_env	*front;
	struct s_env	*last;
	size_t			size;
}					t_env_manager;

#endif