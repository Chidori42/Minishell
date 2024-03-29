/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:04:22 by bramzil           #+#    #+#             */
/*   Updated: 2023/11/14 12:16:33 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_mem(t_list *node, void *ptr, void (*del)(void *))
{
	if (ptr)
		del(ptr);
	if (node)
		ft_lstclear(&node, del);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list				*head;
	t_list				*new_lst;
	void				*ptr;

	if (!lst || !f || !del)
		return (0);
	ptr = f(lst->content);
	new_lst = ft_lstnew(ptr);
	if (!new_lst)
		ft_free_mem(new_lst, ptr, del);
	head = new_lst;
	lst = lst->next;
	while (lst && new_lst)
	{
		ptr = f(lst->content);
		new_lst->next = ft_lstnew(ptr);
		if (!new_lst->next)
		{
			ft_free_mem(head, ptr, del);
			return (0);
		}
		new_lst = new_lst->next;
		lst = lst->next;
	}
	return (head);
}
