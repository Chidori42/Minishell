/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:44:44 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/01 03:33:42 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char				*s2;

	s2 = NULL;
	if (s1)
	{
		s2 = (char *)malloc(ft_strlen(s1) + 1);
		if (s2 == 0)
			return (0);
		ft_strlcpy(s2, s1, (ft_strlen(s1) + 1));
	}
	return (s2);
}
