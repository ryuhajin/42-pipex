/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 21:49:40 by dayou             #+#    #+#             */
/*   Updated: 2023/10/22 16:52:38 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <sys/errno.h>
#include "../libft/libft.h"

void	check_leak(void)
{
	system("leaks --list pipex");
}

int	ft_strcmp_end_n(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*s1_uc;
	unsigned char	*s2_uc;

	s1_uc = (unsigned char *)s1;
	s2_uc = (unsigned char *)s2;
	i = 0;
	
	while (s1_uc[i] == s2_uc[i] && s1_uc[i] && s2_uc[i])
	{
		i++;
	}
	if (s1_uc[i] == '\0' && s2_uc[i] == '\n')
		return 0;
	return (s1_uc[i] - s2_uc[i]);
}

void make_tmp_file (char * argv[])
{
	int tmp;
	char * line;

	tmp = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	line = get_next_line(STDIN_FILENO);
	while (line != NULL && ft_strcmp_end_n(argv[2], line))
	{
		write(tmp, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	close(tmp);
}

int here_doc_check (char * argv)
{
	if (!ft_strncmp("here_doc", argv, ft_strlen(argv)))
		return 1;
	return 0;
}

void wait_for_child (int cmd_cnt)
{
	int i;

	i = 0;
	while (i < cmd_cnt)
	{
		wait(0);
		i++;
	}
}

void check_fd()
{
	int fd = open("main.c", O_RDONLY);
	printf("check fd : %d\n", fd);
	close(fd);
}
int argv_space_check (int argc, char *argv[], int here_doc_flag)
{
	int i;
	int j;

	i = 1;
	if (here_doc_flag == 1)
		i = 3;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] == ' ')
			j++;
		if (j == ft_strlen(argv[i]))
		{
			ft_perror("error : input error");
			return failed;
		}
	}
	return success;
}

int Check_for_argv(int argc, char * argv[], int here_doc_flag)
{
	if (argv_null_check(argc, argv, here_doc_flag) == failed)
		return failed;
	if (argv_space_check(argc, argv, here_doc_flag) == failed)
		return failed;
}

int main(int argc, char * argv[], char ** envp)
{
	t_input * node;
	int cmd_cnt;
	int here_doc_flag;
	// "     " << 인자로 들어왔을때 처리
	// here_doc을 tmp 파일로 사용하기 (limeter xxxxxxxxxx)
	// here_doc_1, here_doc_2
	// access(here_doc_1, F_OK) -> 없으면 이 이름 사용
	// 이미 있으면 i + 1 -> here_doc_2
	// atexit(check_leak);
	if (argc < 5)
	{	
		ft_perror("error : check the argc.");
		return failed;
	}
	// check_fd();
	here_doc_flag = here_doc_check(argv[1]);
	cmd_cnt = argc -3 -here_doc_flag;
    if (Check_for_argv(argc, argv, here_doc_flag) == failed)
		exit(1);
	if (malloc_for_node(&node, argc, cmd_cnt, here_doc_flag) == failed)
		exit(1);
	if (init_input_node(node, argc, argv, envp) == failed)
		exit(1);
	if (here_doc_flag == 1)
		make_tmp_file(argv);
	cmd_print(node);
	path_print(node);
	file_path_print(node);
	make_child(node, envp, cmd_cnt);
	wait_for_child(cmd_cnt);
	clear_node(argc, cmd_cnt, node);
	// check_fd();
	return (0);
}
