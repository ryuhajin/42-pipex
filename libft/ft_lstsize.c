/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:18:28 by dayou             #+#    #+#             */
/*   Updated: 2023/04/10 17:06:38 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*temp;
	int		cnt;

	temp = lst;
	cnt = 0;
	while (temp->next != NULL)
	{
		cnt++;
		temp = temp->next;
	}
	return (cnt);
}
