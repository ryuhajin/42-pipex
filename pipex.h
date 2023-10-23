/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:57:37 by dayou             #+#    #+#             */
/*   Updated: 2023/10/23 20:59:49 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef enum e_status
{
	failed = -1,
	success = 0
}			t_status;

typedef enum e_pipes
{
	read_fd = 0,
	write_fd = 1
}			t_pipe;

typedef struct input
{
	char	***input_str;
	char	**env_path;
	char	**file_path;
	int		**pipes;
	char	**here_doc;
	int		here_doc_flag;
	int		infile_fd;
	int		outfile_fd;
}			t_input;

// access_bonus.c
int			file_access_check(t_input *node, int proc_idx, int cmd_cnt);
int			access_for_cmd(t_input *node, int proc_idx);
int			access_for_infile(t_input *node, int proc_idx);
int			access_for_outfile(t_input *node, int proc_idx);
int			file_redirection_check(t_input *node, int proc_idx,
				int total_pipes);

// check_argv_bonus.c
void		ft_perror(const char *str);
int			argv_null_check(int argc, char *argv[], int here_doc_flag);
int			argv_space_check(int argc, char *argv[], int here_doc_flag);
int			check_for_argv(int argc, char *argv[], int here_doc_flag);

// fork_bonus.c
void		single_cmd_not_require_pipe(t_input *node, char **envp,
				int proc_idx, int cmd_cnt);
int			open_outfile(int proc_idx, t_input *node);
void		wait_for_child(int cmd_cnt);
int			make_child(t_input *node, char **envp, int cmd_cnt);

// free_bonus.c
void		double_pointer_node_free(char **split);
void		triple_pointer_node_free(int argc, int here_doc_flag,
				char **split[]);
void		pipes_free(int cmd_cnt, int **pipes);
void		clear_node(int argc, int cmd_cnt, t_input *node);

// init_bonus.c
int			argv_split(int argc, char **argv, t_input *node);
int			make_pipes(int cmd_cnt, t_input *node);
int			malloc_for_node(t_input **node, int argc, int cmd_cnt,
				int here_doc_flag);
int			init_input_node(t_input *node, int argc, char **argv, char **envp);

// input_bonus.c
char		*search_path_from_env(char **envp);
char		*make_tmp_env_path(char ***input_str, char **env_path, int i,
				int j);
int			finds_cmd_in_env_path(char ***input_str, char **env_path,
				char **file_path, int i);
int			starts_with_directory(char *str);
int			make_file_path(t_input *node, int last_input_idx, int i);

//pipe_bonus.c
void		fd_dup_for_first_cmd(int proc_idx, t_input *node);
void		fd_dup_for_middle_cmd(int proc_idx, t_input *node);
void		fd_dup_for_last_cmd(int proc_idx, t_input *node);
void		pipes_fd_setting(int total_pipes, int proc_idx, t_input *node);

// pipe_bonus2.c
void		close_fd(int total_pipes, int proc_idx, t_input *node);
void		close_fd_all(int total_pipes, t_input *node);
void		child_pipe_setting(t_input *node, int cmd_cnt, int proc_idx);

//print_bonus.c
void		argv_print(t_input *node);
void		path_print(t_input *node);
void		file_path_print(t_input *node);

#endif
