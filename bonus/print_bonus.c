/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 23:07:43 by dayou             #+#    #+#             */
/*   Updated: 2023/10/16 23:08:42 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void cmd_print (t_input * node)
{
	char *** print;
	int i;
	int j;
	
	print = node->argv;
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
	print = node->path;
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
		printf("file_path : %s", print[i]);
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

void	triple_pointer_node_free(int argc, char **split[])
{
	int	i;

	i = 0;
	while (i < argc - 1)
	{
		double_pointer_node_free(split[i]);
		i++;
	}
	free(split);
}

void pipes_free(int argc, int ** fd)
{
	int	i;

	i = 0;
	while (i < argc -4)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

void clear_node(int argc, t_input * node)
{
	double_pointer_node_free(node->path);
	double_pointer_node_free(node->file_path);
	triple_pointer_node_free(argc, node->argv);
	pipes_free(argc, node->fd);
	free(node);
}
