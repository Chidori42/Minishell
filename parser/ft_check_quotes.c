/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:21:53 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/05 11:19:49 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_find_second(char *s, char qt, int i)
{
	while (s && s[++i])
		if (s[i] == qt)
			return (i);
	return (i);
}

int	ft_scape_quotes(char *input, int i)
{
	char		qt;

	if (input)
	{
		qt = input[i];
		while (input[++i] && input[i] != qt)
			;
	}
	return (i);
}

int	ft_check_quotes(char *s)
{
	int			i;
	int			pos;

	i = -1;
	while (s && s[++i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			pos = ft_find_second(s, s[i], i);
			if (s[i] != s[pos])
				return (ft_parse_error(ft_substr(s, i, 1)), -1);
			i = pos;
		}
	}
	return (0);
}
