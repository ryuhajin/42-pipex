/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:36:53 by dayou             #+#    #+#             */
/*   Updated: 2023/10/22 17:12:27 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../libft/libft.h"


void ft_perror (const char * str)
{
	int len;
	len = ft_strlen(str);
	write(2, str, len);
}

void child_pipe_setting (t_input * node, int cmd_cnt, int proc_idx)
{
	close_fd(cmd_cnt -1, proc_idx, node);
	pipes_fd_setting(cmd_cnt -1, proc_idx, node);
}

// cmd1 체크 안해줌

int cmdfile_check(t_input * node, int proc_idx)
{
	if (node->file_path[proc_idx + 1][0] == '\0')
	{
		ft_perror("command not found: ");
		ft_perror(*(node->input_str[proc_idx+1]));
		ft_perror("\n");
		return failed;
	}
	else if (access(node->file_path[proc_idx +1], X_OK) == failed)
	{
		ft_perror(node->file_path[proc_idx+1]);
		ft_perror(": Permission denied\n");
		return failed;
	}
	return success;
}

int infile_check (t_input * node, int proc_idx)
{
	if (access(node->file_path[proc_idx], F_OK) == failed)
	{	
		ft_perror(node->file_path[proc_idx]);
		ft_perror(": No such file or directory\n");
		return failed;
	}
	else if (access(node->file_path[proc_idx], R_OK) == failed)
	{
		ft_perror(node->file_path[proc_idx]);
		ft_perror(": Permission denied\n");
		return failed;
	}
	node->infile_fd = open(node->file_path[0], O_RDONLY);
	return success;
}

// cmd2 체크 안해줌
int outfile_check (t_input * node, int proc_idx)
{	
	if (access(node->file_path[proc_idx +2], F_OK) == success)
	{
		if (access(node->file_path[proc_idx +2], W_OK) == failed)
		{	
			ft_perror(node->file_path[proc_idx+2]);
			ft_perror(": Permission denied\n");
			return failed;
		}
	}
	node->outfile_fd = open_outfile(proc_idx, node);
	return success;
}

int file_redirection_check (t_input * node, int proc_idx, int total_pipes)
{
	int result;
	
	result = 0;
	if (proc_idx == 0)
		result = infile_check(node, proc_idx);
	if (proc_idx == total_pipes)
		result = outfile_check(node, proc_idx);
	return result;
}

int file_access_check(t_input * node, int proc_idx, int cmd_cnt)
{
	int result;
	int total_pipes;

	total_pipes = cmd_cnt-1;
	if (file_redirection_check(node, proc_idx, total_pipes) == failed)
		return failed;
	result = cmdfile_check(node, proc_idx);
	if (result == failed)
		return failed;
	return success;
}

void single_cmd_not_require_pipe(t_input * node, char ** envp, int proc_idx, int cmd_cnt)
{
	if (file_access_check(node, proc_idx, cmd_cnt) == failed)
		exit(1);
	dup2(node->infile_fd, STDIN_FILENO);
	close(node->infile_fd);
	dup2(node->outfile_fd, STDOUT_FILENO);
	close(node->outfile_fd);
	execve(node->file_path[proc_idx +1], node->input_str[proc_idx +1], envp);
	exit(1);
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
			if (cmd_cnt == 1)
				single_cmd_not_require_pipe(node, envp, proc_idx, cmd_cnt);
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
