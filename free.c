/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:35:21 by dayou             #+#    #+#             */
/*   Updated: 2023/10/23 20:52:31 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	double_pointer_node_free(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	triple_pointer_node_free(int argc, int here_doc_flag, char **split[])
{
	int	i;

	i = 0;
	while (i < argc - 1 - here_doc_flag)
	{
		double_pointer_node_free(split[i]);
		i++;
	}
	free(split);
}

void	pipes_free(int cmd_cnt, int **pipes)
{
	int	i;

	i = 0;
	while (i < cmd_cnt - 1)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	clear_node(int argc, int cmd_cnt, t_input *node)
{
	if (node->here_doc_flag)
		unlink(node->file_path[0]);
	double_pointer_node_free(node->env_path);
	double_pointer_node_free(node->file_path);
	triple_pointer_node_free(argc, node->here_doc_flag, node->input_str);
	if (cmd_cnt != 1)
		pipes_free(cmd_cnt, node->pipes);
	free(node);
}
