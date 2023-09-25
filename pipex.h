/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:57:37 by dayou             #+#    #+#             */
/*   Updated: 2023/09/25 20:39:19 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <stdio.h> // 나중에 삭제
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>

typedef enum e_status
{
	failed = -1,
	success = 0
}	t_status;

typedef struct input
{
	char *** cmd;
    char ** path;
	char ** file_path; //file_path[argc]
} t_input;

int	split_start(int argc, char **argv, char **splits[]);
int argv_split (t_input * node, int argc, char ** argv);
int make_input_node (t_input ** node, int argc, char ** argv, char ** envp);
char * search_path (char ** envp);
void temp_free (char *temp, char *temp_file_path);
int check_cmd_file (char ***input_cmd, char **path, char ** file_path);

