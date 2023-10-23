/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:06:35 by dayou             #+#    #+#             */
/*   Updated: 2023/10/23 20:52:50 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fd_dup_for_first_cmd(int proc_idx, t_input *node)
{
	int	right_pipe;

	right_pipe = proc_idx;
	dup2(node->infile_fd, STDIN_FILENO);
	close(node->infile_fd);
	dup2(node->pipes[right_pipe][write_fd], STDOUT_FILENO);
	close(node->pipes[right_pipe][write_fd]);
	close(node->pipes[right_pipe][read_fd]);
}

void	fd_dup_for_middle_cmd(int proc_idx, t_input *node)
{
	int	left_pipe;
	int	right_pipe;

	left_pipe = proc_idx - 1;
	right_pipe = proc_idx;
	dup2(node->pipes[left_pipe][read_fd], STDIN_FILENO);
	close(node->pipes[left_pipe][read_fd]);
	close(node->pipes[left_pipe][write_fd]);
	dup2(node->pipes[right_pipe][write_fd], STDOUT_FILENO);
	close(node->pipes[right_pipe][write_fd]);
	close(node->pipes[right_pipe][read_fd]);
}

void	fd_dup_for_last_cmd(int proc_idx, t_input *node)
{
	int	left_pipe;

	left_pipe = proc_idx - 1;
	dup2(node->pipes[left_pipe][read_fd], STDIN_FILENO);
	close(node->pipes[left_pipe][read_fd]);
	close(node->pipes[left_pipe][write_fd]);
	dup2(node->outfile_fd, STDOUT_FILENO);
	close(node->outfile_fd);
}

void	pipes_fd_setting(int total_pipes, int proc_idx, t_input *node)
{
	if (proc_idx == 0)
		fd_dup_for_first_cmd(proc_idx, node);
	else if (proc_idx == total_pipes)
		fd_dup_for_last_cmd(proc_idx, node);
	else
		fd_dup_for_middle_cmd(proc_idx, node);
}
