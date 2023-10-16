/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:57:37 by dayou             #+#    #+#             */
/*   Updated: 2023/10/15 21:36:32 by dayou            ###   ########.fr       */
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

typedef struct input
{
	char *** argv;
    char ** path;
	char ** file_path; //file_path[argc]
    int ** fd;
} t_input;

int	split_start(int argc, char **argv, char **splits[]);
int argv_split (t_input * node, int argc, char ** argv);
int argv_null_check (char * argv[], int argc);
int make_input_node (t_input ** node, int argc, char ** argv, char ** envp);
char * search_path (char ** envp);
void temp_free (char *temp, char *temp_file_path);
int check_cmd_file (char ***input_cmd, char **path, char ** file_path, int i);
void check_handler(t_input * node, int argc);
int make_child(int argc, t_input * node, char ** envp);
int make_pipes (int argc, t_input * node);
void close_fd_all (int total_pipes, t_input * node);
void close_fd (int total_pipes, int proc_idx, t_input * node);
int fd_handler (int total_pipes, int proc_idx, t_input * node);
