/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:59:12 by dayou             #+#    #+#             */
/*   Updated: 2023/10/17 19:40:20 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../libft/libft.h"

int argv_null_check (char * argv[], int argc)
{
	int i;
	i = 1;
	while (i < argc)
	{
		if (*argv[i] == '\0')
		{
			printf("input error");
			return failed;
		}
		i++;
	}
	return success;
}

int	argv_split(int argc, char **argv, char **splits[], int flag)
{
	char	**temp;
	int		i;
	int		j;
	
	i = flag;
	j = 0;
	if (flag == 1)
		flag = 0;
	else if (flag == 2)
		flag = 1;
	while (i < argc - flag)
	{
		temp = ft_split(argv[i], ' ');
		if (temp == NULL)
			return (failed);
		splits[j] = temp;
		i++;
		j++;
	}
	return (success);
}

int make_input_node (t_input ** node, int argc, char ** argv, char ** envp)
{
	*node = (t_input *)malloc(sizeof(t_input) * 1);
	if (*node == NULL)
		return failed;
	(*node)->file_path = (char **)malloc(sizeof(char *) * argc);
	if ((*node)->file_path == NULL)
		return failed;
	(*node)->file_path[argc - 1] = NULL;
	(*node)->env_path = ft_split(search_path_from_env(envp), ':');
	if ((*node)->env_path == NULL)
		return failed;
	(*node)->input_str = malloc(sizeof(char *) * argc);
	if ((*node)->input_str == NULL)
		return failed;
	(*node)->input_str[argc -1] = NULL;
	if (argv_split(argc, argv, (*node)->input_str, 1) == failed) // 이름 바꾸기
		return failed;
	make_file_path(*node, argc);
	return success;
}

int make_input_node_bonus(t_input ** node, int argc, char ** argv, char ** envp)
{
	*node = (t_input *)malloc(sizeof(t_input) * 1);
	if (*node == NULL)
		return failed;
	(*node)->file_path = (char **)malloc(sizeof(char *) * argc -1);
	if ((*node)->file_path == NULL)
		return failed;
	(*node)->file_path[argc - 2] = NULL;
	(*node)->env_path = ft_split(search_path_from_env(envp), ':');
	if ((*node)->env_path == NULL)
		return failed;
	(*node)->input_str = malloc(sizeof(char *) * argc -1);
	if ((*node)->input_str == NULL)
		return failed;
	(*node)->input_str[argc -2] = NULL;
	if (argv_split(argc, argv, (*node)->input_str, 2) == failed) // 이름 바꾸기
		return failed;
	make_file_path(*node, argc);
	return success;
}

char * search_path_from_env(char ** envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
			return envp[i] + 5;
		i++;
	}
	return NULL;
}

void temp_free (char *temp, char *temp_file_path)
{
	free(temp);
	free(temp_file_path);
}

int finds_argv_in_env_path (char ***argv, char **env_path, char ** file_path, int i)
{
	char * temp;
	char * temp_file_path;
	int j;

	j = 0;
	while (env_path[j])
	{
		temp = ft_strjoin(env_path[j], "/"); //join 할 때마다 malloc 체크 해줘야하는가???
		temp_file_path = ft_strjoin(temp, *(argv[i]));
		if (access(temp_file_path, F_OK) == success)
		{
			file_path[i] = temp_file_path;
			// printf("file %s \n", file_path[i]);
			free(temp);
			break;
		}
		else
			temp_free(temp, temp_file_path);
		j++;
	}
	if (env_path[j] == NULL)
		return failed;
	return success;
}

int check_argv_directory (t_input * node, int i)
{
	const char * path = "./";
	const char * path2 = "../";

	if (*(node->input_str[i][0]) == '/')
		return success;
	if (ft_strnstr(*(node->input_str[i]), path, 2))
		return success;
	if (ft_strnstr(*(node->input_str[i]), path2, 3))
		return success;
	return failed;
}

int starts_with_directory(char *str)
{
	const char * path = "./";
	const char * path2 = "../";

	if (str[0] == '/')
		return success;
	if (ft_strnstr(str, path, 2))
		return success;
	if (ft_strnstr(str, path2, 3))
		return success;
	return failed;
}

void make_file_path(t_input * node, int argc)
{
	int i;
	i = 0;

	while (node->input_str[i])
	{
		if (i == 0 || i == argc-1)
		{
			node->file_path[i] = ft_strdup(*(node->input_str[i]));
			i++;
			continue;
		}
		if (starts_with_directory(*(node->input_str[i])) == success)
			node->file_path[i] = ft_strdup(*(node->input_str[i]));
		else if(finds_argv_in_env_path(node->input_str, node->env_path, node->file_path, i) == failed)
			node->file_path[i] = ft_strdup("");
		i++;
	}
}
