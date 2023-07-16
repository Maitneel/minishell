#include <stdio.h>
#include "parser.h"

void	print_command(t_command *command)
{
	t_redirect_info	*redirect;
	t_args_list		*args;

	fprintf(stderr, "\x1b[36m");
	while (command != NULL)
	{
		fprintf(stderr, "--------------------------------------\n");
		fprintf(stderr, "%-13s : '%s'\n", "command_name",
				command->command_name);
		fprintf(stderr, "%-13s : ", "input list");
		redirect = command->inputs;
		while (redirect != NULL)
		{
			fprintf(stderr, "[%d, '%s'], ", redirect->kind, redirect->arg);
			redirect = redirect->next;
		}
		fprintf(stderr, "\n");
		fprintf(stderr, "%-13s : ", "output list");
		redirect = command->outpus;
		while (redirect != NULL)
		{
			fprintf(stderr, "[%d, '%s'], ", redirect->kind, redirect->arg);
			redirect = redirect->next;
		}
		fprintf(stderr, "\n");
		fprintf(stderr, "%-13s : ", "args");
		args = command->args_list;
		while (args != NULL)
		{
			fprintf(stderr, "%s ", args->string);
			args = args->next;
		}
		fprintf(stderr, "\n");
		fprintf(stderr, "%-13s : '%d'\n", "next_pipe", command->next_pipe);
		command = command->next;
	}
	fprintf(stderr, "--------------------------------------\n");
	fprintf(stderr, "\x1b[39m");
}