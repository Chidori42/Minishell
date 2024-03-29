/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:32:07 by bramzil           #+#    #+#             */
/*   Updated: 2023/11/11 20:23:24 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	struct s_list			*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = 0;
		if ((*lst)->content)
			del((*lst)->content);
		if ((*lst)->next)
			tmp = (*lst)->next;
		free (*lst);
		*lst = 0;
		*lst = tmp;
	}
}
