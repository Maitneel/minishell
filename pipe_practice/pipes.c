/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipess.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dummy <dummy@example.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:22:23 by taksaito          #+#    #+#             */
/*   Updated: 2023/05/19 21:112:57 by dummy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <sys/wait.h>
#include <sys/fcntl.h>
#include <stdlib.h>

int ft_system(int argc, char **argv)
{
    char *path = argv[1];
    char *args[argc - 1];
    for (size_t i = 0; i < argc - 1; i++)
    {
        args[i] = argv[i + 1];
    }
    args[argc - 1] = NULL;
    return execve(path, args, NULL);
}

#define WRITE_FD 1
#define READ_FD 0

int craete_and_run_pipe(int before_fd, const char *command)
{
	fprintf(stderr, "arg_fd : '%d'\n", before_fd);
	fflush(stderr);
	int pipe_fd[2];
	pipe(pipe_fd);
	pid_t pid = fork();
	if (pid == 0) {
		// child
        close(pipe_fd[READ_FD]);
		// dup2(pipe_fd[READ_FD], before_fd);
		// dup2(before_fd, pipe_fd[READ_FD]);
		dup2(before_fd, STDIN_FILENO);
		fprintf(stderr, "run : %s\n", command);
		if (strcmp(command, "READ") == 0)
		{
			char c;
			fprintf(stderr, "read from %d\n", pipe_fd[READ_FD]);
			while (read(STDIN_FILENO, &c, 1))
			{
				fprintf(stderr, "read : %c\n", c);
				fflush(stderr);
			}
			write(STDERR_FILENO, "\n", 1);
		} else {
			system(command);
		}
		fprintf(stderr, "end : %s\n", command);
		fflush(stderr);
		exit(0);
	} else {
		//parent
		// close(pipe_fd[READ_FD]);
		close(pipe_fd[WRITE_FD]);
		fprintf(stderr, "pipe_fd[WRITE_FD] : '%d'\n", pipe_fd[WRITE_FD]);
		fflush(stderr);
		// return pipe_fd[WRITE_FD];
		return pipe_fd[READ_FD];
	}
	return -1;
}

int main(int argc, const char **argv)
{
	if (argc < 2)
		return 0;
	int returned_fd;
	returned_fd = craete_and_run_pipe(STDIN_FILENO, argv[1]);
	for (size_t i = 2; i < argc; i++)
	{
		returned_fd = craete_and_run_pipe(returned_fd, argv[i]);
	}
	dup2(returned_fd, STDOUT_FILENO);
    for (size_t i = 1; i < argc; i++)
    	wait(NULL);
} 

// int main(int argc, char **argv)
// {
//     int out_fd;
//     out_fd = open("out", O_WRONLY | O_CREAT, 0777);
//     int stdin_dup = dup(STDIN_FILENO);
//     int pipe_fd[2];
//     pipe_fd[READ_FD] = 0;
//     pipe_fd[WRITE_FD] = 0;

//     pipe(pipe_fd);
//     // printf("pipe_fd[READ_FD] : '%d'\n", pipe_fd[READ_FD]); // read
//     // printf("pipe_fd[WRITE_FD] : '%d'\n", pipe_fd[WRITE_FD]); // write
//     pid_t pid = fork();
//     if (pid == 0)
//     {
//         // child
//         close(pipe_fd[READ_FD]);
//         dup2(pipe_fd[WRITE_FD], STDOUT_FILENO);
// 	    ft_system(argc, argv);
//         return 0;
//     } else {
//         // parent
//         close(pipe_fd[WRITE_FD]);
//         int child_return;
//         dup2(pipe_fd[READ_FD], STDIN_FILENO);
//         system("grep hello");
//         wait(&child_return);
//     }
// 	close(out_fd);
//     return 0;
// }
