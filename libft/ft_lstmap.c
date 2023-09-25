/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dayou <da1712@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:48:09 by dayou             #+#    #+#             */
/*   Updated: 2023/04/10 17:06:32 by dayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*new_list;
	t_list	*new_head;

	temp = lst;
	new_head = &new_list;
	while (temp->next != NULL)
	{
		new_list = ft_lstnew(f(temp->content));
		ft_lstadd_back(&new_head, new_list);
	}
	return (new_head);
}
