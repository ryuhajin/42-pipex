/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:57:07 by dayou             #+#    #+#             */
/*   Updated: 2023/09/21 17:06:28 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

int main(int argc, char * argv[], char ** envp)
{
    int fd[2];
    if (pipe(fd) == failed)
    {
        perror("pipe error : ");
        exit(1);
    }
    pid_t pid = fork();
    if (pid == failed)
    {
        perror("fork error : ");
        exit(1);
    }
    else if (pid == 0)
    {
        dup2(fd[1], 1);
        close(fd[0]);
    }
    dup2(fd[0], 0);
    close(fd[1]);

    char line[255];

    while(fgets(line, sizeof(line), stdin) != NULL){
        printf("%s", line);
    }

    return 0;
}