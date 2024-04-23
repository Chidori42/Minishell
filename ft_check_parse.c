/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:28:27 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/23 04:08:10 by ael-fagr         ###   ########.fr       */
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
	while (args->tab && args->tab[++i])
	{
		if (ft_check_quotes(args->tab[i]) && ++err)
			return (1);
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
	if (args->tab && !ft_is_operator(args->tab[ref]))
		args->tab[ref] = ft_heredoc(args, args->tab[ref]);
	return (err);
}

int	ft_check_parse(t_pars *args, char *input)
{
	int			i;

	i = -1;
	if (args && input)
	{
		args->tab = ft_split_input(ft_inject_space(input));
		if (args->tab && !ft_strcmp(args->tab[0], "|"))
			return (ft_parse_error(ft_strdup(args->tab[0])), 258);
		while (!g_sig && args->tab && args->tab[++i])
		{
			if (ft_check_quotes(args->tab[i]))
				return (258);
			else if (!ft_strcmp(args->tab[i], "|") && \
				ft_is_operator(args->tab[i - 1]))
				return (ft_parse_error(ft_strdup(args->tab[i])), 258);
			else if (ft_is_redir(args->tab[i]) && (i) && \
				ft_is_redir(args->tab[i - 1]))
				return (ft_parse_error(ft_strdup(args->tab[i])), 258);
			else if (!ft_strcmp(args->tab[i], "<<") && ft_here_it(args, i))
				return (258);
		}
		if (!g_sig && args->tab && ft_is_operator(args->tab[--i]))
			return (ft_parse_error(ft_strdup("\\n")), 258);
	}
	return (g_sig);
}
