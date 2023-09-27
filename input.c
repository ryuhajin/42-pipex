/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:59:12 by dayou             #+#    #+#             */
/*   Updated: 2023/09/27 18:59:50 by dayou            ###   ########.fr       */
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
	(*node)->file_path = (char **)malloc(sizeof(char *) * argc);
	if ((*node)->file_path == NULL)
		return failed;
	(*node)->file_path[argc] = NULL;
	envp_path = search_path(envp);
	if (envp_path == NULL)
		return failed;
	(*node)->path = ft_split(envp_path, ':');
	if ((*node)->path == NULL)
		return failed;
	if (argv_split(*node, argc, argv) == failed)
		return failed;
	check_handler(*node);
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

void temp_free (char *temp, char *temp_file_path)
{
	free(temp);
	free(temp_file_path);
}

int check_cmd_file (char ***input_cmd, char **path, char ** file_path, int i)
{
	char * temp;
	char * temp_file_path;
	int j;

	j = 0;
	while (path[j])
	{
		temp = ft_strjoin(path[j], "/"); //join 할 때마다 malloc 체크 해줘야하는가???
		temp_file_path = ft_strjoin(temp, *(input_cmd[i]));
		if (access(temp_file_path, F_OK) == success)
		{
			file_path[i] = temp_file_path;
			free(temp);
			break;
		}
		else
			temp_free(temp, temp_file_path);
		j++;
	}
	if (path[j] == NULL)
		return failed;
	return success;
}

void check_handler(t_input * node)
{
	int i;
	i = 0;

	while (node->cmd[i])
	{
		if(check_cmd_file(node->cmd, node->path, node->file_path, i) == failed)
			node->file_path[i] = ft_strdup(*(node->cmd[i]));
		i++;
	}

	//권한 확인 와일문 만들기
}
