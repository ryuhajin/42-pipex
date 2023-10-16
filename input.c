/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:59:12 by dayou             #+#    #+#             */
/*   Updated: 2023/10/15 21:43:42 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"
# include "./libft/libft.h"

int argv_null_check (char * argv[], int argc)
{
	int i;
	i = 1;
	while (i < argc)
	{
		printf("%s %d\n", argv[i], i);
		if (*argv[i] == '\0')
		{
			printf("input errer");
			return failed;
		}
		i++;
	}
	return success;
}

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
		node->argv = splits;
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
	check_handler(*node, argc);
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

int check_argv_file (char ***argv, char **path, char ** file_path, int i)
{
	char * temp;
	char * temp_file_path;
	int j;

	j = 0;
	while (path[j])
	{
		temp = ft_strjoin(path[j], "/"); //join 할 때마다 malloc 체크 해줘야하는가???
		temp_file_path = ft_strjoin(temp, *(argv[i]));
		if (access(temp_file_path, F_OK) == success)
		{
			file_path[i] = temp_file_path;
			printf("file %s \n", file_path[i]);
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

int check_argv_directory (t_input * node, int i)
{
	const char * path = "./";
	const char * path2 = "../";

	if (*(node->argv[i][0]) == '/')
		return success;
	if (ft_strnstr(*(node->argv[i]), path, 2))
		return success;
	if (ft_strnstr(*(node->argv[i]), path2, 3))
		return success;
	return failed;
}

void check_handler(t_input * node, int argc)
{
	int i;
	i = 0;

	while (i < argc-1)
	{
		if (check_argv_directory(node, i) == success)
			node->file_path[i] = ft_strdup(*(node->argv[i]));
		else if(check_argv_file(node->argv, node->path, node->file_path, i) == failed)
			node->file_path[i] = ft_strdup(""); // no path file
		i++;
	}
	//권한 확인 와일문 만들기
}
