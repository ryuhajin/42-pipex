/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:06:35 by dayou             #+#    #+#             */
/*   Updated: 2023/10/18 19:59:25 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"
#include "./libft/libft.h"

void close_fd_all (int total_pipes, t_input * node)
{
    int i;
    i = 0;
    while (i < total_pipes)
    {
        close(node->pipes[i][read_fd]);
        close(node->pipes[i][write_fd]);
        i++;
    }
}

void close_fd (int total_pipes, int proc_idx, t_input * node)
{
    int i;

    i = 0;
    while (i < total_pipes)
    {
        if (i == proc_idx -1 || i == proc_idx)
        {
            i++;
            continue;
        }
        close(node->pipes[i][read_fd]);
        close(node->pipes[i][write_fd]);
        i++;
    }
}

int first_infile_check (t_input * node, int proc_idx)
{
	int tmp;
	
	if (access(node->file_path[0], F_OK) == failed)
		printf(" %s: No such file or directory\n", node->file_path[0]);
	else if (access(node->file_path[0], R_OK) == failed)
		printf(" %s: Permission denied\n", node->file_path[0]);
    tmp = open(node->file_path[0], O_RDONLY);
	return tmp;
}

int middle_cmd_file_check(t_input * node, int proc_idx)
{
	if (access(node->file_path[proc_idx +1], F_OK) == failed)
		printf(" %s: No such file or directory\n", node->file_path[proc_idx+1]);
	else if (access(node->file_path[0], X_OK) == failed)
		printf(" %s: Permission denied\n", node->file_path[proc_idx+1]);
}

int last_outfile_check (t_input * node, int proc_idx, int here_doc_flag)
{	
	int tmp;
	
	if (here_doc_flag == 0) // 그 뒤에 쓰는 오픈
	{
		if (access(node->file_path[proc_idx +2], F_OK) == success)
		{
			if (access(node->file_path[proc_idx +2], W_OK) == success)
				tmp = open(*node->file_path[proc_idx + 2], O_WRONLY | O_TRUNC);
			printf(" %s: Permission denied\n", node->file_path[proc_idx+2]);
		}
		else
    		tmp = open(*node->file_path[proc_idx + 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
	{
		if (access(node->file_path[proc_idx +2], F_OK) == success)
		{
			if (access(node->file_path[proc_idx +2], W_OK) == success)
				tmp = open(*node->file_path[proc_idx + 2], O_WRONLY | O_APPEND);
			printf(" %s: Permission denied\n", node->file_path[proc_idx+2]);
		}
		else
    		tmp = open(*node->file_path[proc_idx + 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	return tmp;
}


int file_access_check(t_input * node, int proc_idx, int cmd_cnt)
{
    if (proc_idx == 0)
    {

	}
    else if (proc_idx == cmd_cnt -1) //here_doc_flag
    {
		
	}
    else
	{
		
	}
}

void first_cmd (int total_pipes, int proc_idx, t_input * node)
{
    int tmp;
	int right_pipe;

	right_pipe = proc_idx;
    tmp = open(*node->input_str[0], O_RDONLY);
    if (tmp == -1) // 명령어가 하나일때 (proc 1)
    {
        if (total_pipes != 0)
        {
            close(node->pipes[right_pipe][write_fd]);
            close(node->pipes[right_pipe][read_fd]);
        }
		return;
    }
    dup2(tmp, STDIN_FILENO);
    close(tmp);
    dup2(node->pipes[right_pipe][write_fd], STDOUT_FILENO);
    close(node->pipes[right_pipe][write_fd]);
    close(node->pipes[right_pipe][read_fd]);
}

void middle_cmd(int proc_idx, t_input * node)
{
	int left_pipe;
	int right_pipe;

	left_pipe= proc_idx -1;
	right_pipe = proc_idx;
	
    dup2(node->pipes[left_pipe][read_fd], STDIN_FILENO);
    close(node->pipes[left_pipe][read_fd]);
    close(node->pipes[left_pipe][write_fd]);
    dup2(node->pipes[right_pipe][write_fd], STDOUT_FILENO);
    close(node->pipes[right_pipe][write_fd]);
    close(node->pipes[right_pipe][read_fd]);
}

void last_cmd(int proc_idx, t_input * node)
{
    int tmp;
    int left_pipe;

	left_pipe= proc_idx -1;
    tmp = open(*node->input_str[proc_idx + 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp == -1)
    {
        close(node->pipes[left_pipe][read_fd]);
        close(node->pipes[left_pipe][write_fd]);
		return;
    }
    dup2(node->pipes[left_pipe][read_fd], STDIN_FILENO);
    close(node->pipes[left_pipe][read_fd]);
    close(node->pipes[left_pipe][write_fd]);
    dup2(tmp, STDOUT_FILENO);
    close(tmp);
}

int pipes_setting (int total_pipes, int proc_idx, t_input * node)
{
    if (proc_idx == 0)
        first_cmd(total_pipes, proc_idx, node);
    else if (proc_idx == total_pipes)
        last_cmd(proc_idx, node);
    else
        middle_cmd(proc_idx, node);
    return success;
}
