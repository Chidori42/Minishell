/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:33:05 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/05 11:18:40 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_redir_nbr(char **tab, int *nb, int i)
{
	*nb = 0;
	while (tab && tab[i] && ft_strcmp(tab[i], "|"))
	{
		if (ft_is_redir(tab[i]))
			(*nb) += 2;
		i++;
	}
	return (*nb);
}

int	ft_get_redir(char ***redir, char **tab, int i)
{
	int			j;
	int			rdr_nbr;

	j = -1;
	(*redir) = NULL;
	if (ft_redir_nbr(tab, &rdr_nbr, i))
		(*redir) = (char **)malloc(sizeof(char *) * (rdr_nbr + 1));
	if (!(*redir))
		return (-1);
	while ((*redir) && tab && tab[i] && \
		ft_strcmp(tab[i], "|"))
	{
		if (ft_is_redir(tab[i]) && tab[i + 1])
		{
			(*redir)[++j] = ft_strdup(tab[i]);
			if (!(*redir)[j])
				return (ft_free_2_dm(*redir), -1);
			(*redir)[++j] = ft_strdup(tab[++i]);
			if (!(*redir)[j])
				return (ft_free_2_dm(*redir), -1);
		}
		i++;
	}
	(*redir)[++j] = NULL;
	return (0);
}
