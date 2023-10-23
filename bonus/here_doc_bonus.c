/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:36:57 by dayou             #+#    #+#             */
/*   Updated: 2023/10/23 20:38:39 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "pipex_bonus.h"

int	here_doc_check(char *argv)
{
	if (!ft_strncmp("here_doc", argv, ft_strlen(argv)))
		return (1);
	return (0);
}

int	strcmp_limiter_and_line(const char *s1, const char *s2)
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
		return (0);
	return (s1_uc[i] - s2_uc[i]);
}

char	*make_non_duplicate_name(char *str)
{
	char	*temp;
	int		i;

	i = 0;
	temp = ft_strjoin(str, ft_itoa(i));
	while (access(temp, F_OK) == success)
	{
		free(temp);
		i++;
		temp = ft_strjoin(str, ft_itoa(i));
	}
	return (temp);
}

int	check_here_doc_duplicate(char *argv[], t_input *node)
{
	if (access(argv[1], F_OK) == failed)
	{
		node->here_doc[0] = ft_strdup(argv[1]);
		return (open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644));
	}
	else
	{
		node->here_doc[0] = make_non_duplicate_name(argv[1]);
		return (open((*node->here_doc), O_WRONLY | O_CREAT | O_TRUNC, 0644));
	}
}

void	make_here_doc_file(char *argv[], t_input *node)
{
	int		here_doc_fd;
	char	*line;

	here_doc_fd = check_here_doc_duplicate(argv, node);
	line = get_next_line(STDIN_FILENO);
	while (line != NULL && strcmp_limiter_and_line(argv[2], line))
	{
		write(here_doc_fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	close(here_doc_fd);
}
