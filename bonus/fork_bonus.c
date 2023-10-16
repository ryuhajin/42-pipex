/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:36:53 by dayou             #+#    #+#             */
/*   Updated: 2023/10/16 23:58:28 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus/pipex_bonus.h"

int make_child(int argc, t_input * node, char ** envp)
{
	pid_t pid;
	int proc_idx;

	proc_idx = 0;
	if (make_pipes(argc, node) == failed)
		exit(1);
	while (proc_idx < argc -3)
	{
		pid = fork();
		if (pid == 0)
		{
			if (node->file_path[proc_idx + 1][0] == '\0')
			{
				printf("command not found : %s\n", *(node->argv[proc_idx + 1]));
				exit(1);
			}
			close_fd(argc -4, proc_idx, node);
			if (pipes_setting(argc -4, proc_idx, node) == failed)
				exit(1);
			execve(node->file_path[proc_idx+1], node->argv[proc_idx+1], envp);
			exit(1);
		}
		proc_idx++;
	}
	close_fd_all(argc -4, node);
	return 0;
}
