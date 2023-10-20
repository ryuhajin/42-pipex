/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:16:29 by dayou             #+#    #+#             */
/*   Updated: 2023/10/19 14:56:43 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void cmd_print (t_input * node)
{
	char *** print;
	int i;
	int j;
	
	print = node->input_str;
	i = 0;
	j = 0;
	while (print[i])
	{
		j = 0;
		while(print[i][j])
		{
			printf("argv %d : %s", i, print[i][j]);
			printf("\n");
			j++;
		}
		i++;
	}
}

void path_print (t_input * node)
{
	char ** print;
	int i;

	i = 0;
	print = node->env_path;
	while (print[i])
	{
		printf("path : %s", print[i]);
		printf("\n");
		i++;
	}
}

void file_path_print(t_input * node)
{
	char ** print;
	int i;

	i = 0;
	print = node->file_path;
	while (print[i])
	{
		printf("\n");
		i++;
	}
}

void	double_pointer_node_free(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split[i]);
	free(split);
}

void	triple_pointer_node_free(int argc, int here_doc_flag, char **split[])
{
	int	i;

	i = 0;
	while (i < argc - 1 -here_doc_flag)
	{
		double_pointer_node_free(split[i]);
		i++;
	}
	free(split);
}

void pipes_free(int argc, int ** pipes)
{
	int	i;

	i = 0;
	while (i < argc -4)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void clear_node(int argc, t_input * node)
{
	if (*node->here_doc_flag)
		unlink(node->file_path[0]);
	double_pointer_node_free(node->env_path);
	double_pointer_node_free(node->file_path);
	triple_pointer_node_free(argc, *node->here_doc_flag, node->input_str);
	pipes_free(argc, node->pipes);
	free(node->here_doc_flag);
	free(node);
}
