/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 21:49:40 by dayou             #+#    #+#             */
/*   Updated: 2023/10/23 23:22:33 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "pipex_bonus.h"

int	main(int argc, char *argv[], char **envp)
{
	t_input	*node;
	int		cmd_cnt;
	int		here_doc_flag;

	if (argc < 5)
	{
		ft_perror("error : check the argc.\n");
		return (failed);
	}
	here_doc_flag = here_doc_check(argv[1]);
	cmd_cnt = argc - 3 - here_doc_flag;
	if (check_for_argv(argc, argv, here_doc_flag) == failed)
		exit(1);
	if (malloc_for_node(&node, argc, cmd_cnt, here_doc_flag) == failed)
		exit(1);
	if (here_doc_flag == 1)
		make_here_doc_file(argv, node);
	if (init_input_node(node, argc, argv, envp) == failed)
		exit(1);
	make_child(node, envp, cmd_cnt);
	wait_for_child(cmd_cnt);
	clear_node(argc, cmd_cnt, node);
	return (0);
}
