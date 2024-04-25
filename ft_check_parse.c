/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:28:27 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/25 02:23:02 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_sig;

static int	ft_is_operator(char *s)
{
	if (s && (!ft_strcmp(s, "|") || \
		!ft_strcmp(s, "<") || !ft_strcmp(s, ">") || \
		!ft_strcmp(s, "<<") || !ft_strcmp(s, ">>")))
		return (1);
	return (0);
}

static int	ft_here_it(t_pars *args, int i)
{
	int		  	ref;
	int			err;
	
	err = 0;
	ref = i + 1;
	while (args->tab && args->tab[i++])
	{
		if (ft_check_quotes(args->tab[i]) && ++err)
			return (err);
		else if (!ft_strcmp(args->tab[i], "|") && \
			ft_is_operator(args->tab[i - 1]) && ++err)
		{
			ft_parse_error(ft_strdup(args->tab[i]));
			break;
		}
		else if (ft_is_redir(args->tab[i]) && (i) && \
			ft_is_redir(args->tab[i - 1]) && ++err)
		{
			ft_parse_error(ft_strdup(args->tab[i]));
			break;
		}
	}
	if (ft_heredoc(args, &args->tab[ref]))
		return (1);
	return (err);
}

int	ft_check_parse(t_pars *args, char **tab)
{
	int			i;

	i = -1;
	if (args && tab)
	{
		while (!g_sig && args->tab && args->tab[++i])
		{
			if (ft_check_quotes(args->tab[i]))
				return (258);
			else if (!ft_strcmp(args->tab[0], "|") && (i == 0))
				return (ft_parse_error(ft_strdup(args->tab[0])), 258);
			else if (!ft_strcmp(args->tab[i], "|") && \
				ft_is_operator(args->tab[i - 1]))
				return (ft_parse_error(ft_strdup(args->tab[i])), 258);
			else if (ft_is_redir(args->tab[i]) && (i) && \
				ft_is_redir(args->tab[i - 1]))
				return (ft_parse_error(ft_strdup(args->tab[i])), 258);
			else if (!ft_strcmp(args->tab[i], "<<") && ft_here_it(args, i))
				return (1);
		}
		if (!g_sig && args->tab && ft_is_operator(args->tab[--i]))
			return (ft_parse_error(ft_strdup("\\n")), 258);
	}
	return (g_sig);
}
