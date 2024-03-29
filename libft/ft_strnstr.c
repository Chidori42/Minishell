/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:34:16 by bramzil           #+#    #+#             */
/*   Updated: 2023/11/08 10:35:09 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t					needle_len;
	size_t					i;

	i = 0;
	needle_len = ft_strlen(needle);
	if (!haystack && !len)
		return (0);
	else if (!*needle)
		return ((char *)haystack);
	while (*haystack && (i < len))
	{
		if ((*haystack == *needle) && ((len - i) >= needle_len))
			if (ft_strncmp(haystack, needle, needle_len) == 0)
				return ((char *)haystack);
		haystack++;
		i++;
	}
	return (0);
}
