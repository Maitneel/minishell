/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:29:11 by taksaito          #+#    #+#             */
/*   Updated: 2023/05/14 18:21:21 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

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
// $ cat hoge.txt > out
int main(int argc, char **argv, char **env)
{
    pid_t pid = fork();
    if (pid != 0)
        ft_system(argc, argv);
    else 
        wait(0);
    return 0;
}

