/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:36:53 by dayou             #+#    #+#             */
/*   Updated: 2023/10/18 19:12:57 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int child_pipe_setting (t_input * node, int cmd_cnt, int proc_idx)
{
	close_fd(cmd_cnt -1, proc_idx, node);
	pipes_setting(cmd_cnt -1, proc_idx, node);
}

int make_child(t_input * node, int cmd_cnt, char ** envp)
{
	pid_t pid;
	int proc_idx;

	proc_idx = 0;
	while (proc_idx < cmd_cnt)
	{
		pid = fork();
		if (pid == 0)
		{
			if (node->file_path[proc_idx + 1][0] == '\0')
			{
				printf("command not found : %s\n", *(node->input_str[proc_idx +1]));
				exit(1);
			}
			//file_access_check(node, proc_idx, cmd_cnt)
			//child_pipe_setting
			execve(node->file_path[proc_idx +1], node->input_str[proc_idx +1], envp);
			exit(1);
		}
		proc_idx++;
	}
	// 명령어 갯수만큼 wait
	//wait
	close_fd_all(cmd_cnt -1, node);
	return 0;
}
