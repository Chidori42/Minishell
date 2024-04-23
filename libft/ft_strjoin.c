/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:18:32 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/21 19:49:36 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char				*str;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == 0)
		return (NULL);
	ft_strlcpy(str, s1, (ft_strlen(s1)) + 1);
	ft_strlcpy((str + ft_strlen(s1)), s2, (ft_strlen(s2) + 1));
	return (str);
}
