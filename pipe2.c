/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:27:05 by dayou             #+#    #+#             */
/*   Updated: 2023/10/23 20:52:55 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fd(int total_pipes, int proc_idx, t_input *node)
{
	int	i;

	i = 0;
	while (i < total_pipes)
	{
		if (i == proc_idx - 1 || i == proc_idx)
		{
			i++;
			continue ;
		}
		close(node->pipes[i][read_fd]);
		close(node->pipes[i][write_fd]);
		i++;
	}
}

void	close_fd_all(int total_pipes, t_input *node)
{
	int	i;

	i = 0;
	while (i < total_pipes)
	{
		close(node->pipes[i][read_fd]);
		close(node->pipes[i][write_fd]);
		i++;
	}
}

void	child_pipe_setting(t_input *node, int cmd_cnt, int proc_idx)
{
	close_fd(cmd_cnt - 1, proc_idx, node);
	pipes_fd_setting(cmd_cnt - 1, proc_idx, node);
}
