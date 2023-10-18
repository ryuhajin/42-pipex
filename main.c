/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:57:07 by dayou             #+#    #+#             */
/*   Updated: 2023/10/18 18:16:41 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

void foo()
{
	system("leaks --fullStacks pipex");
}
int main (int argc, char * argv[], char ** envp)
{
	// atexit(foo);
	t_input * node;
	int cmd_cnt;
	int here_doc_flag;

	here_doc_flag = 0;
	cmd_cnt = argc -3 -here_doc_flag;
	printf("cmd_cnt: %d\n", cmd_cnt);
	// if (argc != 5)
	// 	exit(1);
	if (argv_null_check(argv, argc) == failed)
		exit(1);
	if (malloc_for_node(&node, argc, cmd_cnt, here_doc_flag) == failed)
	{	
		printf("malloc failed\n");
		exit(1);
	}
	if (init_input_node(node, argc, argv, envp) == failed)
	{
		printf("init failed\n");
		exit(1);
	}
	cmd_print(node);
	path_print (node);
	file_path_print(node);

	make_child(node, cmd_cnt, envp);
	clear_node(argc, node);
	return (0);
}
