/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:06:35 by dayou             #+#    #+#             */
/*   Updated: 2023/10/19 13:28:59 by dayou            ###   ########.fr       */
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

void first_cmd (int proc_idx, t_input * node)
{
    int tmp;
	int right_pipe;

	right_pipe = proc_idx;
	tmp = open(node->file_path[0], O_RDONLY);
	
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

int open_outfile (int proc_idx, t_input * node)
{
	int tmp;

    tmp = failed;
	if (*(node->here_doc_flag) == 0)
	{
		if (access(node->file_path[proc_idx +2], F_OK) == success)
			tmp = open(node->file_path[proc_idx +2], O_WRONLY | O_TRUNC);
		else
			tmp = open(node->file_path[proc_idx + 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (*(node->here_doc_flag) == 1)
	{
		if (access(node->file_path[proc_idx +2], F_OK) == success)
			tmp = open(node->file_path[proc_idx + 2], O_WRONLY | O_APPEND);
		else
			tmp = open(node->file_path[proc_idx + 2], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	return tmp;
}

void last_cmd(int proc_idx, t_input * node)
{
    int tmp;
    int left_pipe;

	left_pipe= proc_idx -1;
	tmp = open_outfile(proc_idx, node);
	
    dup2(node->pipes[left_pipe][read_fd], STDIN_FILENO);
    close(node->pipes[left_pipe][read_fd]);
    close(node->pipes[left_pipe][write_fd]);
    dup2(tmp, STDOUT_FILENO);
    close(tmp);
}

void pipes_fd_setting (int total_pipes, int proc_idx, t_input * node)
{
    if (proc_idx == 0)
        first_cmd(proc_idx, node);
    else if (proc_idx == total_pipes)
        last_cmd(proc_idx, node);
    else
        middle_cmd(proc_idx, node);
}
