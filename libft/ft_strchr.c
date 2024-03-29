/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:44:59 by bramzil           #+#    #+#             */
/*   Updated: 2024/01/18 12:41:18 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s || !c)
		return (NULL);
	while (*s && (*s != (char)c))
		s++;
	if ((*s == (char)c) || ((char)c == '\0'))
		return ((char *) s);
	return (0);
}
