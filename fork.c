/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:36:53 by dayou             #+#    #+#             */
/*   Updated: 2023/10/17 21:30:26 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int make_child(int cmd_cnt, int here_doc_flag, t_input * node, char ** envp)
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
			if (node->file_path[proc_idx + 1 + here_doc][0] == '\0')
			{
				printf("command not found : %s\n", *(node->input_str[proc_idx + 1]));
				exit(1);
			}
			close_fd(argc -4, proc_idx, node);
			if (pipes_setting(argc -4, proc_idx, node) == failed)
				exit(1);
			execve(node->file_path[proc_idx+1], node->input_str[proc_idx+1], envp);
			exit(1);
		}
		proc_idx++;
	}
	close_fd_all(argc -4, node);
	return 0;
}
