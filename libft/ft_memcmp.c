/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:44:18 by bramzil           #+#    #+#             */
/*   Updated: 2023/11/12 20:07:48 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (!n)
		return (0);
	while (--n && (*(unsigned char *)s1) == (*(unsigned char *)s2))
	{
		s2++;
		s1++;
	}
	return ((*(unsigned char *)s1) - (*(unsigned char *)s2));
}
