/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:18:43 by bramzil           #+#    #+#             */
/*   Updated: 2023/11/14 21:45:04 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t				dstlen;
	size_t				srclen;
	size_t				ref;

	srclen = ft_strlen(src);
	if (!dst && !dstsize)
		return (srclen);
	dstlen = ft_strlen(dst);
	ref = dstlen;
	if (dstsize < dstlen)
		return (dstsize + srclen);
	while (*src && (dstlen + 1) < dstsize)
	{
		dst[dstlen] = *src;
		dstlen++;
		src++;
	}
	if (ref < dstlen)
		dst[dstlen] = '\0';
	return (ref + srclen);
}
