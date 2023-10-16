/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <dayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:06:35 by dayou             #+#    #+#             */
/*   Updated: 2023/10/15 21:29:34 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

int make_pipes (int argc, t_input * node)
{
    int i;
    int j;
    int ** pipes_arry;

    i = argc -4;
    j = 0;
    pipes_arry = (int **)malloc(i * sizeof(int *));
    node->fd = pipes_arry;

    while (j < i)
    {
        node->fd[j] = (int *)malloc(2 * sizeof(int));
        if (pipe(node->fd[j]) == failed)
            return failed;
        j++;
    }
    return success;
}

void close_fd_all (int total_pipes, t_input * node)
{
    int i;
    i = 0;
    while (i < total_pipes)
    {
        close(node->fd[i][0]);
        close(node->fd[i][1]);
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
        close(node->fd[i][0]);
        close(node->fd[i][1]);
        i++;
    }
}

void first_pipe (int total_pipes, t_input * node)
{
    int tmp;

    tmp = open(*node->argv[0], O_RDONLY);
    if (tmp == -1) // 명령어가 하나일때 (proc 1)
    {
        if (total_pipes != 0)
        {
            close(node->fd[0][1]);
            close(node->fd[0][0]);
        }
        printf("no such file or directory: %s\n", *node->argv[0]);
		return;
    }
    dup2(tmp, STDIN_FILENO);
    close(tmp);
    dup2(node->fd[0][1], STDOUT_FILENO);
    close(node->fd[0][1]);
    close(node->fd[0][0]);
}

void middle_pipes(int proc_idx, t_input * node)
{
    dup2(node->fd[proc_idx -1][0], STDIN_FILENO);
    close(node->fd[proc_idx -1][0]);
    close(node->fd[proc_idx -1][1]);
    dup2(node->fd[proc_idx][1], STDOUT_FILENO);
    close(node->fd[proc_idx][1]);
    close(node->fd[proc_idx][0]);
}

void last_pipe(int proc_idx, t_input * node)
{
    int tmp;
    
    tmp = open(*node->argv[proc_idx + 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp == -1)
    {
        close(node->fd[proc_idx -1][0]);
        close(node->fd[proc_idx -1][1]);
        printf("no such file or directory: %s\n", *node->argv[proc_idx + 2]);
		return;
    }
    dup2(node->fd[proc_idx -1][0], STDIN_FILENO);
    close(node->fd[proc_idx -1][0]);
    close(node->fd[proc_idx -1][1]);
    dup2(tmp, STDOUT_FILENO);
    close(tmp);
}

int fd_handler (int total_pipes, int proc_idx, t_input * node)
{
    if (proc_idx == 0)
        first_pipe(total_pipes, node);
    else if (proc_idx == total_pipes)
        last_pipe(proc_idx, node);
    else
        middle_pipes(proc_idx, node);
    return success;
}
