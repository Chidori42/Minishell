/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:45:56 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/24 23:21:38 by bramzil          ###   ########.fr       */
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

int	ft_get_cmd(char ***data, char **tab, int i)
{
	int			j;
	int			nb;

	j = -1;
	nb = ft_cmd_elmnts(tab, i);
	if (!nb)
		return (0);
	(*data) = (char **)malloc(sizeof(char *) * (nb + 1));
	if (!(*data))
		return (-1);
	while (*data && tab && tab[i] && ft_strcmp(tab[i], "|"))
	{
		if ((i == 0 && !ft_is_redir(tab[i])) || \
			(0 < i && !ft_is_redir(tab[i]) && \
			!ft_is_redir(tab[i - 1])))
		{
			(*data)[++j] = ft_strdup(tab[i]);
			if (!((*data)[j]))
				return (ft_free_2_dm(*data), -1);
		}
		i++;
	}
	(*data)[++j] = NULL;
    return (0);
}
