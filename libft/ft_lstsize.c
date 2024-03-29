/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:04:00 by bramzil           #+#    #+#             */
/*   Updated: 2023/11/06 11:29:15 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t			lst_len;

	lst_len = 0;
	if (lst == 0)
		return (0);
	while (++lst_len && lst->next)
		lst = lst->next;
	return (lst_len);
}
