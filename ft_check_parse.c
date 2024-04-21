/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:28:27 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/21 10:03:42 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_operator(char *s)
{
	if (s && (!ft_strcmp(s, "|") || \
		!ft_strcmp(s, "<") || !ft_strcmp(s, ">") || \
		!ft_strcmp(s, "<<") || !ft_strcmp(s, ">>")))
		return (1);
	return (0);
}

int	ft_check_parse(t_pars *args, char *input)
{
	int			i;

	i = -1;
	if (input)
	{
		args->tab = ft_split_input(ft_inject_space(input));
		if (!ft_strcmp(args->tab[0], "|"))
			return (ft_parse_error(ft_strdup(args->tab[0])), 258);
		while (args->tab[++i])
		{
			if (ft_check_quotes(args->tab[i]))
				return (258);
			else if (!ft_strcmp(args->tab[i], "|") && \
				ft_is_operator(args->tab[i - 1]))
				return (ft_parse_error(ft_strdup(args->tab[i])), 258);
			if (ft_is_redir(args->tab[i]) && (i) && \
				ft_is_redir(args->tab[i - 1]))
				return (ft_parse_error(ft_strdup(args->tab[i])), 258);
		}
		if (ft_is_operator(args->tab[--i]))
			return (ft_parse_error(ft_strdup("\\n")), 258);
		ft_expander(args, args->tab);
	}
	return (0);
}
