/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:36:53 by dayou             #+#    #+#             */
/*   Updated: 2023/09/28 21:07:14 by dayou            ###   ########.fr       */
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
		printf("first pid %d %s %s %s\n", getpid(), node->file_path[1], node->cmd[1][0], node->cmd[1][1]);
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
	printf("end %d\n", wait(NULL));
	printf("end %d\n", wait(NULL));
	// while (wait())
	// {
	// 	;
	// }
	// wait : (어떤) 자식 프로세스가 끝나기를 기다린다. (호출한 프로세스를 일시중지, 자식이 끝나서 stat_loc 정보를 가질 때 까지)
	// waitpid : 특정한 자식 프로세스가 끝나기를 기다린다. (여러가지 옵션이 있지만, WNOHANG은 자식 프로세스가 stat_loc을 알려주기 전까지 호출자 프로세스를 블락시키지 않는다)
	while(i<n)
	{
		wait();
		// 끝난 처리
	}
	while (i < n)
	{
		while (waitpid(WNOHANG) == 0)
		{
			sleep(10);
			printf("is running\n");
		}
		// 끝난 처리
	}
	wait vs waitpid ?
		waitpid는 어떻게 쓸거임?
			프로세스 수 만큼 while에서 waitpid한다
			[뭘 한다]
			부모프로세스에서 할 일이 있으면 while+WNOHANG 돌리면서 한다
		wait은 어떻게 쓸거임?
			프로세스 수 만큼 while에서 wait한다
			자식 프로세스 수만큼 쓴다.
		근데, 결론은 wait도 먼저 끝나는 순서대로 처리를 할 수 있다.

	2개면 wait -> 왜?
	100개면 waitpid -> 왜?
	뭐가 됐든 waitpid <<
	
	오류>> wait한번 하면 다 기다려주는 줄
		자식 프로세스를 기다리는게 끝났을 때, 자식 프로세스의 종료 상태를 보내줌
		종료상태를 통해서 처리해줄 수 있기 때문
		wait는 한가지 자식만 볼 수 있는 것이 아닌가?
			기다리는 동안 내가 아무것도 할 수 없음.
			무조건적으로 어떤 프로세스가 끝나기를 기다림.
			동시에 끝난 경우, 어떻게 처리할까?
				맨 처음 받은 리턴값으로 처리를 하겠지
				wait?
					stat이 바뀜 << wait을 호출을 해야 바뀌는게 아님? << (x)
				waitpid는 될까?
					모르겠다. -> 실험 (을 통해서 정답을 찾는다) (o)
							-> 정답을 찾는다 (x)
	return 0;
}
