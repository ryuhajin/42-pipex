/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:57:37 by dayou             #+#    #+#             */
/*   Updated: 2023/10/18 21:42:53 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <stdio.h> // 나중에 삭제
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef enum e_status
{
	failed = -1,
	success = 0
}	t_status;

typedef enum e_pipes
{
	read_fd = 0,
	write_fd = 1
}	t_pipe;

typedef struct input
{
	char *** input_str;
    char ** env_path;
	char ** file_path; //file_path[argc]
    int ** pipes;
	int * here_doc_flag;
} t_input;

// init.c
int malloc_for_node (t_input ** node, int argc, int cmd_cnt, int here_doc_flag);
int init_input_node (t_input * node, int argc, char ** argv, char ** envp);
int make_pipes (int cmd_cnt, t_input * node);

//input.c
int argv_null_check (char * argv[], int argc);
int	argv_split(int argc, char **argv, char **splits[]);
char * search_path_from_env(char ** envp);
char * make_tmp_env_path (char ***input_str, char ** env_path, int i, int j);
int finds_cmd_in_env_path (char ***input_str, char **env_path, char ** file_path, int i);
int check_argv_directory (t_input * node, int i);
int starts_with_directory(char *str);
int make_file_path(t_input * node, int argc, int i);

//pipe.c
void close_fd_all (int total_pipes, t_input * node);
void close_fd (int total_pipes, int proc_idx, t_input * node);
void first_cmd (int total_pipes, int proc_idx, t_input * node);
void middle_cmd(int proc_idx, t_input * node);
void last_cmd(int proc_idx, t_input * node);
int pipes_setting (int total_pipes, int proc_idx, t_input * node);

//fork.c
int make_child(t_input * node, char ** envp, int cmd_cnt);

//print.c
void cmd_print (t_input * node);
void path_print (t_input * node);
void file_path_print(t_input * node);
void	double_pointer_node_free(char **split);
void	triple_pointer_node_free(int argc, char **split[]);
void pipes_free(int argc, int ** pipes);
void clear_node(int argc, t_input * node);
