/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taksaito <taksaito@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 21:21:22 by taksaito          #+#    #+#             */
/*   Updated: 2023/05/14 21:47:35 by taksaito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>

int main()
{
    int dup_fd = open("temp", O_WRONLY);
    write(dup_fd, "fugaa\n", 6);
    dup2(dup_fd, STDOUT_FILENO);
    printf("%d\n", dup_fd);
 
    write(STDOUT_FILENO, "hello\n", 6);
}


// int main()
// {
//     int dup_fd = dup(STDIN_FILENO);
//     char c;
//     pid_t pid = fork();
//     if (pid == 0)
//     {
//         while(read(dup_fd, &c, 1))
//             write(STDERR_FILENO, &c, 1);
//     } else {
//         while(read(STDIN_FILENO, &c, 1))
//             write(STDERR_FILENO, &c, 1);
//     }
    
// }