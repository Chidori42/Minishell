/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_scaper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 01:24:53 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/11 04:01:12 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_rm_scaper(char **tmp, int i)
{
	char		*scd;

	if ((*tmp)[i] == '\\' && ((*tmp)[i + 1] == '\'' || \
		(*tmp)[i + 1] == '\"'))
	{
		scd = ft_substr((*tmp), (i + 1), ft_strlen((*tmp)));
		(free((*tmp)), (*tmp) = ft_strs_join(ft_substr((*tmp), \
			0, i), scd));
	}
}

static void	ft_inject_scaper(char **tmp, int *i)
{
	char		*scd;
	
	scd = ft_strs_join(ft_strdup("\\"), \
		ft_substr((*tmp), (*i), ft_strlen((*tmp))));
	(free((*tmp)), (*tmp) = ft_strs_join(ft_substr((*tmp), \
		0, (*i)), scd));
	(*i) += 1;
}

int	ft_remove_scaper(char ***tab)
{
	int			i;
	int			j;
	char		*tmp;

	j = -1;
	while ((*tab) && ((*tab)[++j]))
	{
		(i = -1, tmp = ft_strdup((*tab)[j]));
		while (tmp && tmp[++i])
			if (tmp[i] == '\\' && (tmp[i + 1] == '\'' || \
				tmp[i + 1] == '\"'))
				ft_rm_scaper(&tmp, i);
		if (tmp)
			(free((*tab)[j]), ((*tab)[j] = tmp));
		else
			return (-1);
	}
	return (0);
}


char	*ft_add_scaper(char *str)
{
	int			i;
	char		qt;
	char		*tmp;

	(i = -1, tmp = ft_strdup(str));
	while (tmp && tmp[++i])
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
		{
			qt = tmp[i];
			while (tmp[++i] && tmp[i] != qt)
				if ((tmp[i] == '\'' || tmp[i] == '\"'))
					ft_inject_scaper(&tmp, &i);
		}
	}
	return (tmp);
}
