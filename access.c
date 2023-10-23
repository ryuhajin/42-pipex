/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:19:02 by dayou             #+#    #+#             */
/*   Updated: 2023/10/23 20:52:21 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	file_access_check(t_input *node, int proc_idx, int cmd_cnt)
{
	int	result;
	int	total_pipes;

	total_pipes = cmd_cnt - 1;
	if (file_redirection_check(node, proc_idx, total_pipes) == failed)
		return (failed);
	result = access_for_cmd(node, proc_idx);
	if (result == failed)
		return (failed);
	return (success);
}

int	access_for_cmd(t_input *node, int proc_idx)
{
	if (node->file_path[proc_idx + 1][0] == '\0')
	{
		ft_perror("command not found: ");
		ft_perror(*(node->input_str[proc_idx + 1]));
		ft_perror("\n");
		return (failed);
	}
	else if (access(node->file_path[proc_idx + 1], X_OK) == failed)
	{
		ft_perror(node->file_path[proc_idx + 1]);
		ft_perror(": Permission denied\n");
		return (failed);
	}
	return (success);
}

int	access_for_infile(t_input *node, int proc_idx)
{
	if (access(node->file_path[proc_idx], F_OK) == failed)
	{
		ft_perror(node->file_path[proc_idx]);
		ft_perror(": No such file or directory\n");
		return (failed);
	}
	else if (access(node->file_path[proc_idx], R_OK) == failed)
	{
		ft_perror(node->file_path[proc_idx]);
		ft_perror(": Permission denied\n");
		return (failed);
	}
	node->infile_fd = open(node->file_path[0], O_RDONLY);
	return (success);
}

int	access_for_outfile(t_input *node, int proc_idx)
{
	if (access(node->file_path[proc_idx + 2], F_OK) == success)
	{
		if (access(node->file_path[proc_idx + 2], W_OK) == failed)
		{
			ft_perror(node->file_path[proc_idx + 2]);
			ft_perror(": Permission denied\n");
			return (failed);
		}
	}
	node->outfile_fd = open_outfile(proc_idx, node);
	return (success);
}

int	file_redirection_check(t_input *node, int proc_idx, int total_pipes)
{
	int	result;

	result = 0;
	if (proc_idx == 0)
		result = access_for_infile(node, proc_idx);
	if (proc_idx == total_pipes)
		result = access_for_outfile(node, proc_idx);
	return (result);
}
