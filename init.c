/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:05:55 by dayou             #+#    #+#             */
/*   Updated: 2023/10/19 14:26:15 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "./libft/libft.h"

int make_pipes (int cmd_cnt, t_input * node)
{
    int total_pipes;
    int i;

    total_pipes = cmd_cnt -1; //pipe는 cmd보다 항상 1개 작다
    node->pipes = (int **)malloc(sizeof(int *) * total_pipes);
    if (node->pipes == NULL)
	{	printf("node->pipex?\n");
		return failed;
	}
	i = 0;
    while (i < total_pipes)
    {
        node->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (node->pipes[i] == NULL)
			return failed;
        if (pipe(node->pipes[i]) == failed)
            return failed;
        i++;
    }
    return success;
}

int malloc_for_node (t_input ** node, int argc, int cmd_cnt, int here_doc_flag)
{
	(*node) = (t_input *)malloc(sizeof(t_input) * 1);
	if ((*node) == NULL)
		return failed;
	(*node)->file_path = (char **)malloc(sizeof(char *) * argc);
	if ((*node)->file_path == NULL)
		return failed;
	(*node)->file_path[argc -1 -here_doc_flag] = NULL;
	(*node)->input_str = malloc(sizeof(char *) * argc);
	if ((*node)->input_str == NULL)
		return failed;
	(*node)->input_str[argc -1 -here_doc_flag] = NULL;
	if (make_pipes(cmd_cnt, (*node)) == failed)
		return failed;
	(*node)->here_doc_flag = (int *)malloc(sizeof(int) * 1);
	if ((*node)->here_doc_flag == NULL)
		return failed;
	*((*node)->here_doc_flag) = here_doc_flag;
	return success;
}

int init_input_node (t_input * node, int argc, char ** argv, char ** envp)
{
	int last_input_idx;

	last_input_idx = argc -2 -*(node->here_doc_flag); //here_doc 요주의
	printf("last_input_idx = %d\n", last_input_idx);
	(node)->env_path = ft_split(search_path_from_env(envp), ':');
	if((node)->env_path == NULL)
		return failed;
	if (argv_split(argc, argv, (node)->input_str) == failed)
		return failed;
	if (make_file_path(node, last_input_idx, 0) == failed)
		return failed;
	return success;
}

