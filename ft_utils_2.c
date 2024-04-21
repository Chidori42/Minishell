/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:14:10 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/21 10:54:58 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_redir(char *s)
{
	if (s)
	{
		if (!ft_strcmp("<", s) || !ft_strcmp(">", s) || \
			!ft_strcmp("<<", s) || !ft_strcmp(">>", s))
			return (1);
	}
	return (0);
}

int	ft_free_2_dm(char **arr)
{
	int			i;

	i = -1;
	while (arr && arr[++i])
		free (arr[i]);
	free (arr);
	return (0);
}

int	ft_check_flu_ct(char *s, int i)
{
	int			rmid;

	rmid = i;
	while (i && s[--i])
	{
		if ((s[i] < 9 || 13 < s[i]) && s[i] != 32)
		{
			if (s[i] == '|' || s[i] == '<' || s[i] == '>')
				return (ft_parse_error(ft_strdup(&s[rmid])), -1);
			else
				return (0);
		}
	}
	return (1);
}

static int	ft_cmd_elmnts(char **tab, int i)
{
	int			nb;

	nb = 0;
	while (tab && tab[i] && ft_strcmp(tab[i], "|"))
	{
		if ((i == 0 && !ft_is_redir(tab[i])) || \
			(0 < i && !ft_is_redir(tab[i]) && \
			!ft_is_redir(tab[i - 1])))
			nb++;
		i++;
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
	nb = ft_cmd_elmnts(tab, i);
	if (nb)
	{
		cmd = (char **)malloc(sizeof(char *) * (nb + 1));
		while (cmd && tab && tab[i] && \
			ft_strcmp(tab[i], "|"))
		{
			if ((i == 0 && !ft_is_redir(tab[i])) || \
				(0 < i && !ft_is_redir(tab[i]) && \
				!ft_is_redir(tab[i - 1])))
				cmd[++j] = ft_strdup(tab[i]);
			i++;
		}
		cmd[++j] = NULL;
	}
	return (cmd);
}
