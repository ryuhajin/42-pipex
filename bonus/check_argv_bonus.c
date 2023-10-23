/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:59:12 by dayou             #+#    #+#             */
/*   Updated: 2023/10/23 20:38:31 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "pipex_bonus.h"

void	ft_perror(const char *str)
{
	int	len;

	len = ft_strlen(str);
	write(2, str, len);
}

int	argv_null_check(int argc, char *argv[], int here_doc_flag)
{
	int	i;

	i = 1;
	if (here_doc_flag == 1)
		i = 3;
	while (i < argc)
	{
		if (*argv[i] == '\0')
		{
			ft_perror("error : input error\n");
			return (failed);
		}
		i++;
	}
	return (success);
}

int	argv_space_check(int argc, char *argv[], int here_doc_flag)
{
	int	i;
	int	j;

	i = 1;
	if (here_doc_flag == 1)
		i = 3;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] == ' ')
			j++;
		if (j == (int)ft_strlen(argv[i]))
		{
			ft_perror("error : input error\n");
			return (failed);
		}
		i++;
	}
	return (success);
}

int	check_for_argv(int argc, char *argv[], int here_doc_flag)
{
	if (argv_null_check(argc, argv, here_doc_flag) == failed)
		return (failed);
	if (argv_space_check(argc, argv, here_doc_flag) == failed)
		return (failed);
	return (success);
}
