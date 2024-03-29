/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:14:24 by bramzil           #+#    #+#             */
/*   Updated: 2023/11/15 10:41:46 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t					i;

	i = n;
	if (!src && !dst)
		return (0);
	else if (dst == src)
		return ((void *)src);
	while (n--)
		*(char *)dst++ = *(char *)src++;
	return (dst - i);
}
