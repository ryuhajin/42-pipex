/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 21:49:40 by dayou             #+#    #+#             */
/*   Updated: 2023/10/16 23:47:26 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../libft/libft.h"

void make_tmp_file (char * argv[])
{
	int tmp;
	char * line;

	tmp = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	line = get_next_line(STDIN_FILENO);
	while (line != NULL && ft_strncmp(argv[2], line, ft_strlen(argv[2])))
	{
		write(tmp, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(tmp);
}

int main(int argc, char * argv[], char ** envp)
{
	t_input * node;

	if (argc < 5)
		return (0);
    if (argv_null_check(argv, argc) == failed)
		exit(1);
	if (!ft_strncmp("here_doc", argv[1], ft_strlen(argv[1])))
	{
		make_tmp_file(argv);
		if (make_input_node_bonus(&node, argc, argv, envp)== failed)
			exit(1);
		make_child(argc, node, envp);
		// unlink(*(node->argv[0]));
	}
	else
	{
		if (make_input_node(&node, argc, argv, envp)== failed)
			exit(1);
		make_child(argc, node, envp);
	}
	clear_node(argc, node);
}
