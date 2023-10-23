/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:16:29 by dayou             #+#    #+#             */
/*   Updated: 2023/10/23 21:18:47 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	argv_print(t_input *node)
{
	char	***print;
	int		i;
	int		j;

	print = node->input_str;
	i = 0;
	j = 0;
	while (print[i])
	{
		j = 0;
		while (print[i][j])
		{
			printf("argv %d : %s", i, print[i][j]);
			printf("\n");
			j++;
		}
		i++;
	}
}

void	path_print(t_input *node)
{
	char	**print;
	int		i;

	i = 0;
	print = node->env_path;
	while (print[i])
	{
		printf("env_path : %s\n", print[i]);
		i++;
	}
}

void	file_path_print(t_input *node)
{
	char	**print;
	int		i;

	i = 0;
	print = node->file_path;
	while (print[i])
	{
		printf("file_path %d: %s\n", i, print[i]);
		i++;
	}
}
