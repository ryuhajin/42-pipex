/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:36:53 by dayou             #+#    #+#             */
/*   Updated: 2023/12/22 22:04:00 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	single_cmd_not_require_pipe(t_input *node, char **envp, int proc_idx,
		int cmd_cnt)
{
	if (file_access_check(node, proc_idx, cmd_cnt) == failed)
		exit(1);
	dup2(node->infile_fd, STDIN_FILENO);
	close(node->infile_fd);
	dup2(node->outfile_fd, STDOUT_FILENO);
	close(node->outfile_fd);
	execve(node->file_path[proc_idx + 1], node->input_str[proc_idx + 1], envp);
	exit(1);
}

int	open_outfile(int proc_idx, t_input *node)
{
	int	tmp;

	tmp = failed;
	if (node->here_doc_flag == 0)
		tmp = open(node->file_path[proc_idx + 2], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	else if (node->here_doc_flag == 1)
		tmp = open(node->file_path[proc_idx + 2], O_WRONLY | O_CREAT | O_APPEND,
				0644);
	return (tmp);
}

void	wait_for_child(int cmd_cnt)
{
	int	i;

	i = 0;
	while (i < cmd_cnt)
	{
		wait(0);
		i++;
	}
}

int	make_child(t_input *node, char **envp, int cmd_cnt)
{
	pid_t	pid;
	int		proc_idx;

	proc_idx = 0;
	while (proc_idx < cmd_cnt)
	{
		pid = fork();
		if (pid == 0)
		{
			if (cmd_cnt == 1)
				single_cmd_not_require_pipe(node, envp, proc_idx, cmd_cnt);
			if (file_access_check(node, proc_idx, cmd_cnt) == failed)
				exit(1);
			child_pipe_setting(node, cmd_cnt, proc_idx);
			execve(node->file_path[proc_idx + 1], node->input_str[proc_idx + 1],
				envp);
			exit(1);
		}
		proc_idx++;
	}
	close_fd_all(cmd_cnt - 1, node);
	return (0);
}
