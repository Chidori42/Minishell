/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:29:36 by bramzil           #+#    #+#             */
/*   Updated: 2023/11/08 12:27:43 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char				*str;
	size_t				end;
	size_t				s1_len;

	end = 0;
	if (!s1)
		return (0);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	s1_len = ft_strlen(s1);
	while (s1_len-- && ft_strchr(set, s1[s1_len]))
		end++;
	str = (char *)malloc(ft_strlen(s1) + 1 - end);
	if (str == 0)
		return (0);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1 - end);
	return (str);
}
