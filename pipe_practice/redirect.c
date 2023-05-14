/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:22:23 by taksaito          #+#    #+#             */
/*   Updated: 2023/05/14 18:42:10 by taksaito         ###   ########.fr       */
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
    dup2(out_fd, STDOUT_FILENO);
	ft_system(argc, argv);
	close(out_fd);	
}
