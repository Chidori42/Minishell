/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:44:59 by bramzil           #+#    #+#             */
/*   Updated: 2023/11/09 10:34:34 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t				slen;

	slen = ft_strlen(s);
	s += slen;
	while ((*s != (char)c) && slen--)
		s--;
	if (*s == (char)c)
		return ((char *) s);
	return (0);
}
