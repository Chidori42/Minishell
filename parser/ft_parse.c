/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 01:11:05 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/06 03:28:54 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_is_operator(char *s)
{
	if (s && (!ft_strcmp(s, "|") || \
		!ft_strcmp(s, "<") || !ft_strcmp(s, ">") || \
		!ft_strcmp(s, "<<") || !ft_strcmp(s, ">>")))
		return (1);
	return (0);
}

static int	ft_check_token(char **tab, int *st, int i)
{
	if (ft_check_quotes(tab[i]))
		return ((*st = 1), ft_get_status(0, 258, 1), -1);
	else if ((i == 0) && !ft_strcmp(tab[0], "|"))
		return (ft_parse_error(ft_strdup(tab[0])), -1);
	else if (!ft_strcmp(tab[i], "|") && ft_is_operator(tab[i - 1]))
		return ((*st = 1), ft_parse_error(ft_strdup(tab[i])), -1);
	else if (ft_is_operator(tab[i]) && !tab[i + 1])
		return ((*st = 1), ft_parse_error(ft_strdup("newline")), -1);
	else if (ft_is_redir(tab[i]) && ft_is_operator(tab[i + 1]))
		return ((*st = 1), ft_parse_error(ft_strdup(tab[i + 1])), -1);
	return (0);
}

int	ft_parse(t_pars *args, char **tab)
{
	int			i;
	int			j;
	int			st;
	int			end;

	i = -1;
	st = 0;
	end = -1;
	while (!st && tab && tab[++i] && (i != end))
	{
		j = i;
		if (ft_check_token(tab, &st, i))
			return (1);
		else if (!ft_strcmp(tab[i], "<<") && \
			!ft_is_operator(tab[i + 1]))
		{
			while ((end == -1) && tab[++j] && tab[j + 1])
				if (ft_check_token(tab, &st, j))
					end = j;
			st = ft_heredoc(args, &tab[i + 1]);
		}
	}
	return (st);
}
