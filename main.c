/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:57:07 by dayou             #+#    #+#             */
/*   Updated: 2023/10/16 22:57:11 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

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

void foo()
{
	system("leaks --fullStacks pipex");
}
void	two_pointer_node_free(char **split)
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
		two_pointer_node_free(split[i]);
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
	two_pointer_node_free(node->path);
	two_pointer_node_free(node->file_path);
	triple_pointer_node_free(argc, node->argv);
	pipes_free(argc, node->fd);
	free(node);
}

int main (int argc, char * argv[], char ** envp)
{
	// atexit(foo);
	t_input * node;
	///cat ./cat ../cat | cat  상대경로 절대경로 등 경로로 찾는 케이스 1 / 패스로 찾는 케이스 2
	// heredoc 처리, 인자를 히어독 파일이름으로 바꿈
	// cmd 한개일때 처리.
	if (argc != 5)
		return (0);
	if (argv_null_check(argv, argc) == failed)
		exit(1);
	if (make_input_node(&node, argc, argv, envp) == failed)
		exit(1); // input malloc error
	// cmd_print(node);
	// path_print(node);
	// file_path_print(node);
	make_child(argc, node, envp);
	clear_node(argc, node);
	return (0);
}

