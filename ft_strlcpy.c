/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeltif <abdeltif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 19:31:27 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/03/28 01:35:18 by abdeltif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlcpy(char *dst, char *src, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[j] != '\0')
		j++;
	if (len == 0)
		return (j);
	while (src[i] && i < len - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (j);
}
