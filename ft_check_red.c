/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:18:39 by bramzil           #+#    #+#             */
/*   Updated: 2024/03/18 00:41:37 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_red_left(char *s, int i)
{
	while (i && s[--i])
	{
		if ((s[i] < 9 || 13 < s[i]) && s[i] != 32)
		{
			if (s[i] == '>' || s[i] == '<' || s[i] == '|' || \
				s[i] == '&')
				return (1);
			else
				return (0);
		} 
	}
	return (0);
}

int	ft_check_redir(char *s, int *i)
{
	if (s[*i] == s[*i + 1])
	{
		if (ft_check_red_left(s, *i))
			return (ft_parse_error(ft_substr(s, *i, 2)), -1);
		*i += 1;
	}
	else if (ft_check_red_left(s, *i))
		return (ft_parse_error(ft_substr(s, *i, 1)), -1);
	return (0);
}
