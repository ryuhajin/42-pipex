/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:57:07 by dayou             #+#    #+#             */
/*   Updated: 2023/10/19 16:13:03 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"
#include "./libft/libft.h"

void foo()
{
	system("leaks --fullStacks pipex");
}

int here_doc_check (char * argv[])
{
	if (!ft_strncmp("here_doc", argv[1], ft_strlen(argv[1])))
		return 1;
	return 0;
}

void wait_for_child (int cmd_cnt)
{
	int i;

	i = 0;
	while (i < cmd_cnt)
	{
		wait(0);
		i++;
	}
}

int main (int argc, char * argv[], char ** envp)
{
	// atexit(foo);
	t_input * node;
	int cmd_cnt;
	int here_doc_flag;

	// if (argc != 5)
	// 	exit(1);
	if (argv_null_check(argv, argc) == failed)
		exit(1);
	here_doc_flag = here_doc_check(argv);
	cmd_cnt = argc -3 -here_doc_flag;
	if (malloc_for_node(&node, argc, cmd_cnt, here_doc_flag) == failed)
		exit(1);
	if (init_input_node(node, argc, argv, envp) == failed)
		exit(1);
	cmd_print(node);
	path_print (node);
	file_path_print(node);
	make_child(node, envp, cmd_cnt);
	wait_for_child(cmd_cnt);
	clear_node(argc, node);
	return (0);
}
