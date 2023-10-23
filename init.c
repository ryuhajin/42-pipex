/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:05:55 by dayou             #+#    #+#             */
/*   Updated: 2023/10/23 23:38:59 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "pipex.h"
#include <stdio.h> // 삭제하기

int	argv_split(int argc, char **argv, t_input *node)
{
	char	**temp;
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (node->here_doc_flag == 1)
	{
		node->input_str[0] = node->here_doc;
		i = 3;
		j = 1;
	}
	while (i < argc)
	{
		temp = ft_split(argv[i], ' ');
		if (temp == NULL)
			return (failed);
		node->input_str[j] = temp;
		i++;
		j++;
	}
	return (success);
}

int	make_pipes(int cmd_cnt, t_input *node)
{
	int	total_pipes;
	int	i;

	total_pipes = cmd_cnt - 1;
	if (total_pipes == 0)
		return (success);
	node->pipes = (int **)malloc(sizeof(int *) * total_pipes);
	if (node->pipes == NULL)
		return (failed);
	i = 0;
	while (i < total_pipes)
	{
		node->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (node->pipes[i] == NULL)
			return (failed);
		if (pipe(node->pipes[i]) == failed)
			return (failed);
		i++;
	}
	return (success);
}

int	malloc_for_node(t_input **node, int argc, int cmd_cnt, int here_doc_flag)
{
	(*node) = (t_input *)malloc(sizeof(t_input) * 1);
	if ((*node) == NULL)
		return (failed);
	(*node)->file_path = (char **)malloc(sizeof(char *) * (argc - here_doc_flag));
	if ((*node)->file_path == NULL)
		return (failed);
	(*node)->file_path[argc - 1 - here_doc_flag] = NULL;
	(*node)->input_str = malloc(sizeof(char *) * (argc - here_doc_flag));
	if ((*node)->input_str == NULL)
		return (failed);
	(*node)->input_str[argc - 1 - here_doc_flag] = NULL;
	if (make_pipes(cmd_cnt, (*node)) == failed)
		return (failed);
	if (here_doc_flag == 1)
	{
		(*node)->here_doc = (char **)malloc(sizeof(char *) * 2);
		if ((*node)->here_doc == NULL)
			return (failed);
		(*node)->here_doc[1] = NULL;
	}
	(*node)->here_doc_flag = here_doc_flag;
	return (success);
}

int	init_input_node(t_input *node, int argc, char **argv, char **envp)
{
	int		last_input_idx;
	char	*temp_env_path;

	last_input_idx = argc - 2 - node->here_doc_flag;
	temp_env_path = search_path_from_env(envp);
	if (temp_env_path == NULL)
		(node)->env_path = ft_split("", ':');
	else
		(node)->env_path = ft_split(temp_env_path, ':');
	if ((node)->env_path == NULL)
		return (failed);
	if (argv_split(argc, argv, node) == failed)
		return (failed);
	if (make_file_path(node, last_input_idx, -1) == failed)
		return (failed);
	return (success);
}
