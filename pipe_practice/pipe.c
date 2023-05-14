/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:22:23 by taksaito          #+#    #+#             */
/*   Updated: 2023/05/14 19:12:11 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/fcntl.h>

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

int main(int argc, char **argv)
{
    int out_fd;
    out_fd = open("out", O_WRONLY | O_CREAT, 0777);
    int stdin_dup = dup(STDIN_FILENO);
    int pipe_fd[2];
    pipe_fd[0] = 0;
    pipe_fd[1] = 0;

    pipe(pipe_fd);
    // printf("pipe_fd[0] : '%d'\n", pipe_fd[0]); // read
    // printf("pipe_fd[1] : '%d'\n", pipe_fd[1]); // write
    pid_t pid = fork();
    if (pid == 0)
    {
        // child
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
	    ft_system(argc, argv);
        return 0;
    } else {
        // parent
        close(pipe_fd[1]);
        int child_return;
        wait(&child_return);
        char c;
        // dup2(STDIN_FILENO, pipe_fd[0]);
        while(read(pipe_fd[0], &c, 1))
            write(STDOUT_FILENO, &c, 1);
    }
    return 0;
	close(out_fd);	
}
// */