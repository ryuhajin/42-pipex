/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:36:53 by dayou             #+#    #+#             */
/*   Updated: 2023/09/27 23:00:05 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <signal.h>

int make_child(int * fd, t_input * node, char ** envp)
{
	int tmp;
	pid_t pid[2];

	pid[0] = fork();
	if (pid[0] == 0)
	{
		printf("first pid %d\n", getpid());
		tmp = open(*node->cmd[0], O_RDONLY);
		if (tmp == -1)
			exit(1);
		close(fd[0]); // pipe read close
		dup2(tmp, STDIN_FILENO); // open file fd -> stdin copy
		close(tmp);
		dup2(fd[1], STDOUT_FILENO); // pipe write fd -> stdout copy
		close(fd[1]); //pipe write close
		execve(node->file_path[1], node->cmd[1], envp);
		exit(1);
	}
	pid[1] = fork();
	if (pid[1] == 0)
	{
		printf("second pid %d\n", getpid());
		tmp = open(*node->cmd[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (tmp == -1)
			return (failed);
		close(fd[1]); // pipe write close
		dup2(tmp, STDOUT_FILENO); // open file fd -> stdout
		close(tmp);
		dup2(fd[0], STDIN_FILENO); //pipe read -> stdin
		close(fd[0]);
		execve(node->file_path[2], node->cmd[2], envp);
		exit(1);
	}

	close(fd[0]);
	close(fd[1]);
	printf("end %d\n", wait(0));
	printf("end %d\n", wait(0));
	// while (waitpid(-1, 0, WNOHANG) > -1)
	// {
	// 	;
	// }
	return 0;
}
