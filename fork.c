/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:36:53 by dayou             #+#    #+#             */
/*   Updated: 2023/10/03 23:35:06 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int make_child(int argc, t_input * node, char ** envp)
{
	pid_t pid;
	int proc_idx;

	proc_idx = 0;
	make_pipes(argc, node);
	while (proc_idx < argc -3)
	{
		pid = fork();
		if (pid == 0)
		{
			printf(">>[child] : %d %s\n", proc_idx, node->file_path[proc_idx+1]);
			close_fd(argc -4, proc_idx, node);
			if (fd_handler(argc -4, proc_idx, node) == failed)
				exit(1);
			execve(node->file_path[proc_idx+1], node->argv[proc_idx+1], envp);
			exit(1);
		}
		proc_idx++;
	}
	close_fd_all(argc -4, node);
	return 0;
}
