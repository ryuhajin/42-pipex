/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:57:37 by dayou             #+#    #+#             */
/*   Updated: 2023/10/17 21:10:41 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <stdio.h> // 나중에 삭제
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

typedef enum e_status
{
	failed = -1,
	success = 0
}	t_status;

typedef enum e_read_status
{
	read_failed = -1,
	read_EOF = 0,
}		t_read_status;

typedef enum e_new_line_status
{
	no_new_line = 0,
	make_new_line = 1,
	line_malloc_failed = 2
}		t_make_line_status;

typedef struct input
{
	char *** input_str;
    char ** env_path;
	char ** file_path; //file_path[argc]
    int ** pipes;
} t_input;

int	argv_split(int argc, char **argv, char **splits[], int flag);
int argv_null_check (char * argv[], int argc);
int make_input_node (t_input ** node, int argc, char ** argv, char ** envp);
int make_input_node_bonus(t_input ** node, int argc, char ** argv, char ** envp);
char * search_path_from_env (char ** envp);
void temp_free (char *temp, char *temp_file_path);
int finds_argv_in_env_path(char ***input_cmd, char **path, char ** file_path, int i);
int starts_with_directory(char *str);
void make_file_path(t_input * node, int argc);
int make_child(int argc, t_input * node, char ** envp);
int make_pipes (int argc, t_input * node);
void close_fd_all (int total_pipes, t_input * node);
void close_fd (int total_pipes, int proc_idx, t_input * node);
int pipes_setting (int total_pipes, int proc_idx, t_input * node);
char	*get_next_line(int fd);
char	*ft_strdup_gnl(char *s1);
char	*ft_strjoin_gnl(char *s1, char *s2, ssize_t size);
size_t	ft_strlcpy_gnl(char *dest, char *src);
ssize_t	find_newline(char *buff, ssize_t *size);
ssize_t	remainder_find_n(int fd, char **line,
			char remainder[][BUFFER_SIZE + 1]);
ssize_t	read_file(int fd, char **line, char remainder[][BUFFER_SIZE + 1]);
char	*read_flag_check(ssize_t flag, char *line);
void cmd_print (t_input * node);
void path_print (t_input * node);
void file_path_print(t_input * node);
void	double_pointer_node_free(char **split);
void	triple_pointer_node_free(int argc, char **split[]);
void pipes_free(int argc, int ** fd);
void clear_node(int argc, t_input * node);

#endif
