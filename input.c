/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:59:12 by dayou             #+#    #+#             */
/*   Updated: 2023/10/18 18:53:46 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "./libft/libft.h"

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

int	argv_split(int argc, char **argv, char **splits[])
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
	return (success);
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

char * make_tmp_env_path (char ***input_str, char ** env_path, int i, int j)
{
	char * temp;
	char * temp_file_path;

	temp = ft_strjoin(env_path[j], "/");
	if (temp == NULL)
		return NULL;
	temp_file_path = ft_strjoin(temp, *(input_str[i]));
	if (temp_file_path == NULL)
		return NULL;
	free(temp);
	return temp_file_path;
}

int finds_cmd_in_env_path (char ***input_str, char **env_path, char ** file_path, int i)
{
	char * temp_file_path;
	int j;

	j = 0;
	while (env_path[j])
	{
		temp_file_path = make_tmp_env_path(input_str, env_path, i, j);
		if (temp_file_path == NULL)
			return failed;
		if (access(temp_file_path, F_OK) == success)
		{
			file_path[i] = temp_file_path;
			break;
		}
		else
			free(temp_file_path);
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

int make_file_path(t_input * node, int last_input_idx, int i)
{
	while (node->input_str[i])
	{
		if (i == 0 || i == last_input_idx)
		{
			node->file_path[i] = ft_strdup(*(node->input_str[i]));
			if (node->file_path[i] == NULL)
				return failed;
			i++;
			continue;
		}
		if (starts_with_directory(*(node->input_str[i])) == success)
		{
			node->file_path[i] = ft_strdup(*(node->input_str[i]));
			if (node->file_path[i] == NULL)
				return failed;
		}
		else if(finds_cmd_in_env_path(node->input_str, node->env_path, node->file_path, i) == failed)
		{	
			node->file_path[i] = ft_strdup("");
			if (node->file_path[i] == NULL)
				return failed;
		}
		i++;
	}
	return success;
}
