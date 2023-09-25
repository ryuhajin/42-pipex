/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:59:12 by dayou             #+#    #+#             */
/*   Updated: 2023/09/25 18:36:43 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"
# include "./libft/libft.h"

int	split_start(int argc, char **argv, char **splits[])
{
	char	**temp;
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		temp = ft_split(argv[i], ' ');
		if (temp == NULL)
			return (failed);
		splits[j] = temp;
		i++;
		j++;
	}
	splits[j] = NULL;
	return (success);
}

int argv_split (t_input * node, int argc, char ** argv)
{
	char	***splits;

	splits = malloc(sizeof(char *) * argc);
	if (splits == NULL)
		return failed;
	if (!split_start(argc, argv, splits))
	{	
		node->cmd = splits;
		return success;
	}
	return failed;
}

int make_input_node (t_input ** node, int argc, char ** argv, char ** envp)
{
	char * envp_path;
	
	*node = (t_input *)malloc(sizeof(t_input) * 1);
	if (*node == NULL)
		return failed;
	envp_path = search_path(envp);
	if (envp_path == NULL)
		return failed;
	(*node)->path = ft_split(envp_path, ':');
	if ((*node)->path == NULL)
		return failed;
	if (argv_split(*node, argc, argv) == failed)
		return failed;
	return success;
}

char * search_path (char ** envp)
{
	int i;
	char * path;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
		{
			path = ft_strdup(envp[i] + 5);
			return path;
		}
		i++;
	}
	return NULL;
}

