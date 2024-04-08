/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:28:27 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/07 09:52:14 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_last(char *input)
{
	int			l;

	if (input)
	{
		l = ft_strlen(input);
		while (l && input[--l])
		{
			if (input[l] == '|')
				return (1);
			else if (input[l] == '<' || input[l] == '>')
				return (ft_parse_error(ft_strdup("\\n")), -1);
			else if (input[l] != 32 && (input[l] < 9 || \
				13 < input[l]))
				break ;
		}
	}
	return (0);
}

int	ft_check_parse(char *input)
{
	int			i;

	i = -1;
	while (input && input[++i])
	{
		if ((input[i] == '|' || input[i] == '&') && \
			ft_check_flu_ct(input, i))
			return (-1);
		else if ((input[i] == '\'' || input[i] == '\"') && \
			ft_check_quotes(input))
			return (-1);
		else if ((input[i] == '>' || input[i] == '<') && \
			ft_check_redir(input, &i))
			return (-1);
	}
	return (ft_check_last(input));
}
