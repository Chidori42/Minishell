/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:33:05 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/21 12:12:10 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_redir_nbr(char **tab, int i)
{
	int			nb;

	nb = 0;
	while (tab && tab[i] && ft_strcmp(tab[i], "|"))
	{
		if (ft_is_redir(tab[i]))
			nb += 2;
		i++;
	}
	return (nb);
}

char	**ft_get_redir(t_pars *args, char **tab, int i)
{
	(void)		args;
	int			j;
	int			rdr_nbr;
    char		**std;

	j = -1;
    std = NULL;
	rdr_nbr = ft_redir_nbr(tab, i);
	std = (char **)malloc(sizeof(char *) * (rdr_nbr + 1));
    while (std && tab && tab[i] && \
		ft_strcmp(tab[i], "|"))
    {
		if (ft_is_redir(tab[i]) && tab[i + 1])
		{
			std[++j] = ft_strdup(tab[i]);
			std[++j] = ft_strdup(tab[++i]);
		}
		i++;
    }
	std[++j] = NULL;
	return (std);
}