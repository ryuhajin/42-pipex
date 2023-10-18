/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:36:53 by dayou             #+#    #+#             */
/*   Updated: 2023/10/18 15:32:20 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus/pipex_bonus.h"

int make_child(int cmd_cnt, t_input * node, char ** envp)
{
	pid_t pid;
	int proc_idx;

	proc_idx = 0;
	if (make_pipes(cmd_cnt, node) == failed)
		exit(1);
	while (proc_idx < cmd_cnt)
	{
		pid = fork();
		if (pid == 0)
		{
			if (node->file_path[proc_idx + 1][0] == '\0')
			{
				printf("command not found : %s\n", *(node->input_str[proc_idx + 1]));
				exit(1);
			}
			close_fd(cmd_cnt -1, proc_idx, node);
			if (pipes_setting(cmd_cnt -1, proc_idx, node) == failed)
				exit(1);
			execve(node->file_path[proc_idx+1], node->input_str[proc_idx+1], envp);
			exit(1);
		}
		proc_idx++;
	}
	close_fd_all(cmd_cnt -1, node);
	return 0;
}
