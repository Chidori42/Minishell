/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:21:53 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/14 20:25:27 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_find_second(char *s, char qt, int i)
{
	while (s && s[++i])
		if ((s[i] == qt) && (!i || s[i - 1] != '\\'))
			return (i);
	return (i);
}

int	ft_scape_quotes(char *input, int i)
{
	char		qt;

	if (input)
	{
		qt = input[i];
		while (input[++i] && ((input[i] != qt) || \
			((input[i] == qt) && (!i || \
				input[i - 1] == '\\'))))
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
		if ((s[i] == '\"' || s[i] == '\'') && \
			(!i || (s[i] != '\\')))
		{
			pos = ft_find_second(s, s[i], i);
			if ((s[i] != s[pos]) || (s[pos - 1] == '\\'))
				return (ft_parse_error(ft_substr(s, i, 1)), -1);
			i = pos;
		}
	}
	return (0);
}
