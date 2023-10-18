/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:06:35 by dayou             #+#    #+#             */
/*   Updated: 2023/10/17 21:30:43 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

int make_pipes (int argc, int not_command, t_input * node)
{
    int number_of_pipes;
    int i;

    number_of_pipes = argc -not_command -1; //argc -4 (not_cmd = ./pipex, infile, outfile) -1 (pipe는 cmd보다 항상 1개 작다)
    i = 0;
    node->pipes = (int **)malloc(number_of_pipes * sizeof(int *));
    
    while (i < number_of_pipes)
    {
        node->pipes[i] = (int *)malloc(2 * sizeof(int));
        if (pipe(node->pipes[i]) == NULL)
            return failed;
        i++;
    }
    return success;
}

void close_fd_all (int total_pipes, t_input * node)
{
    int i;
    i = 0;
    while (i < total_pipes)
    {
        close(node->pipes[i][read_fd]);
        close(node->pipes[i][write_fd]);
        i++;
    }
}

void close_fd (int total_pipes, int proc_idx, t_input * node)
{
    int i;

    i = 0;
    while (i < total_pipes)
    {
        if (i == proc_idx -1 || i == proc_idx)
        {
            i++;
            continue;
        }
        close(node->pipes[i][read_fd]);
        close(node->pipes[i][write_fd]);
        i++;
    }
}

void first_cmd (int total_pipes, t_input * node)
{
    int tmp;

    tmp = open(*node->input_str[0], O_RDONLY);
    if (tmp == -1) // 명령어가 하나일때 (proc 1)
    {
        if (total_pipes != 0)
        {
            close(node->pipes[0][write_fd]);
            close(node->pipes[0][read_fd]);
        }
        printf("no such file or directory: %s\n", *node->input_str[0]);
		return;
    }
    dup2(tmp, STDIN_FILENO);
    close(tmp);
    dup2(node->pipes[0][write_fd], STDOUT_FILENO);
    close(node->pipes[0][write_fd]);
    close(node->pipes[0][read_fd]);
}

void middle_cmd(int proc_idx, t_input * node)
{
    dup2(node->pipes[proc_idx -1][read_fd], STDIN_FILENO);
    close(node->pipes[proc_idx -1][read_fd]);
    close(node->pipes[proc_idx -1][write_fd]);
    dup2(node->pipes[proc_idx][write_fd], STDOUT_FILENO);
    close(node->pipes[proc_idx][write_fd]);
    close(node->pipes[proc_idx][read_fd]);
}

void last_cmd(int proc_idx, t_input * node)
{
    int tmp;
    
    tmp = open(*node->input_str[proc_idx + 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp == -1)
    {
        close(node->pipes[proc_idx -1][read_fd]);
        close(node->pipes[proc_idx -1][write_fd]);
        printf("no such file or directory: %s\n", *node->input_str[proc_idx + 2]);
		return;
    }
    dup2(node->pipes[proc_idx -1][read_fd], STDIN_FILENO);
    close(node->pipes[proc_idx -1][read_fd]);
    close(node->pipes[proc_idx -1][write_fd]);
    dup2(tmp, STDOUT_FILENO);
    close(tmp);
}

int pipes_setting (int total_pipes, int proc_idx, t_input * node)
{
    if (proc_idx == 0)
        first_cmd(total_pipes, node);
    else if (proc_idx == total_pipes)
        last_cmd(proc_idx, node);
    else
        middle_cmd(proc_idx, node);
    return success;
}
