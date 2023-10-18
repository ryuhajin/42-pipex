/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:36:53 by dayou             #+#    #+#             */
/*   Updated: 2023/10/18 22:54:58 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void child_pipe_setting (t_input * node, int cmd_cnt, int proc_idx)
{
	close_fd(cmd_cnt -1, proc_idx, node);
	pipes_fd_setting(cmd_cnt -1, proc_idx, node);
}

int first_infile_check (t_input * node, int proc_idx)
{
	if (access(node->file_path[0], F_OK) == failed)
	{	
		printf(" %s: No such file or directory\n", node->file_path[0]);
		return failed;
	}
	else if (access(node->file_path[0], R_OK) == failed)
	{
		printf(" %s: Permission denied\n", node->file_path[0]);
		return failed;
	}
	return success;
}

int middle_cmdfile_check(t_input * node, int proc_idx)
{
	if (access(node->file_path[proc_idx +1], F_OK) == failed)
	{
		printf(" %s: No such file or directory\n", node->file_path[proc_idx+1]);
		return failed;
	}
	else if (access(node->file_path[0], X_OK) == failed)
	{
		printf(" %s: Permission denied\n", node->file_path[proc_idx+1]);
		return failed;
	}
	return success;
}

int last_outfile_check (t_input * node, int proc_idx)
{	
	if (access(node->file_path[proc_idx +2], F_OK) == success)
	{
		if (access(node->file_path[proc_idx +2], W_OK) == failed)
		{	
			printf(" %s: Permission denied\n", node->file_path[proc_idx+2]);
			return failed;
		}
	}
	return success;
}

int file_access_check(t_input * node, int proc_idx, int cmd_cnt)
{
	int result;
	int total_pipes;

	total_pipes = cmd_cnt-1;
    if (proc_idx == 0)
		result = first_infile_check(node, proc_idx);
    else if (proc_idx == total_pipes)
		result = last_outfile_check(node, proc_idx);
    else
		result = middle_cmdfile_check(node, proc_idx);
	if (result == failed)
		return failed;
	return success;
}



int make_child(t_input * node, char ** envp, int cmd_cnt)
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
				printf("command not found : %s\n", node->file_path[proc_idx +1]);
				exit(1);
			}
			if (file_access_check(node, proc_idx, cmd_cnt) == failed)
				exit(1);
			child_pipe_setting(node, cmd_cnt, proc_idx);
			execve(node->file_path[proc_idx +1], node->input_str[proc_idx +1], envp);
			exit(1);
		}
		proc_idx++;
	}
	close_fd_all(cmd_cnt -1, node);
	return 0;
}
