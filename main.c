/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:57:07 by dayou             #+#    #+#             */
/*   Updated: 2023/10/15 21:44:10 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int main (int argc, char * argv[], char ** envp)
{
	int fd[2];
	t_input * node;
	///cat ./cat ../cat | cat  상대경로 절대경로 등 경로로 찾는 케이스 1 / 패스로 찾는 케이스 2
	if (pipe(fd) == failed)
		exit(1); //error exit
	// heredoc 처리, 인자를 히어독 파일이름으로 바꿈
	// cmd 한개일때 처리.
	if (argv_null_check(argv, argc) == failed)
		exit(1);
	if (make_input_node(&node, argc, argv, envp) == failed)
		exit(1); // input malloc error
	cmd_print(node);
	path_print(node);
	file_path_print(node);
	make_child(argc, node, envp);
	return (0);
}
