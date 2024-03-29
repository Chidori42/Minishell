/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:14:10 by bramzil           #+#    #+#             */
/*   Updated: 2024/03/27 17:17:02 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_redir(char *s)
{
	if (s)
	{
		if (!ft_strcmp("<", s) || !ft_strcmp(">", s) || \
			!ft_strcmp("<<", s) || !ft_strcmp(">>", s))
			return (1);
	}
	return (0);
}

int	ft_check_flu_ct(char *s, int i)
{
	while (i && s[--i])
	{
		if ((s[i] < 9 || 13 < s[i]) && s[i] != 32)
		{
			if (s[i] == '|' || s[i] == '&' || s[i] == '<' || \
				s[i] == '>')
				return (-1);
			else
				return (0);
		} 
	}
	return (1);
}

static int	ft_cmd_elmnts(char **tab)
{
	int			i;
	int			nb;

	i = -1;
	nb = 0;
	while (tab && tab[++i])
	{
		if ((i == 0 && !ft_is_redir(tab[i])) || \
			(0 < i && !ft_is_redir(tab[i]) && \
			!ft_is_redir(tab[i - 1])))
			nb++;
	}
	return (nb);
}

char	**ft_get_cmd(char **tab, int i)
{
	int			j;
	int			nb;
    char		**cmd;

	j = -1;
    cmd = NULL;
	nb = ft_cmd_elmnts(tab);
	if (nb)
	{
		cmd = (char **)malloc(sizeof(char *) * (nb + 1));
		while (cmd && tab && tab[i] && \
			ft_strcmp(tab[i], "|"))
		{
			if ((i == 0 && !ft_is_redir(tab[i])) || \
				(0 < i && !ft_is_redir(tab[i]) && \
				!ft_is_redir(tab[i - 1])))
				cmd[++j] = tab[i];
			i++;
		}
		cmd[++j] = NULL;
	}
    return (cmd);
}