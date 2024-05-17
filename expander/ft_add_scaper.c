/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_scaper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 01:24:53 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/14 19:45:15 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_rm_scaper(char **tmp, int i)
{
	char		*frt;
	char		*scd;

	if ((*tmp)[i] == '\\' && ((*tmp)[i + 1] == '\'' || \
		(*tmp)[i + 1] == '\"'))
	{
		frt = ft_substr((*tmp), 0, i);
		scd = ft_substr((*tmp), (i + 1), ft_strlen((*tmp)));
		(free((*tmp)), (*tmp) = ft_strs_join(frt, scd));
	}
}

static void	ft_inject_scaper(char **tmp, int i)
{
	char		*ptr;

	ptr = ft_strs_join(ft_substr((*tmp), 0, i), \
		ft_strdup("\\"));
	if (ptr)
	{
		ptr = ft_strs_join(ptr, ft_substr((*tmp), i, \
			ft_strlen((*tmp))));
		if (ptr)
			(free((*tmp)), (*tmp) = ptr);
		else
			(free((*tmp)), (*tmp) = NULL);
	}
}

int	ft_remove_scaper(char ***tab)
{
	int			i;
	int			j;
	char		*tmp;

	j = -1;
	if ((*tab) && !ft_strcmp((*tab)[0], "export"))
		return (0);
	while ((*tab) && ((*tab)[++j]))
	{
		i = -1;
		tmp = ft_strdup((*tab)[j]);
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

	i = -1;
	tmp = ft_strdup(str);
	while (tmp && tmp[++i])
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
		{
			qt = tmp[i];
			while (tmp && tmp[++i] && tmp[i] != qt)
			{
				if ((tmp[i] == '\'' || tmp[i] == '\"'))
					ft_inject_scaper(&tmp, i++);
				if (tmp && !tmp[i])
					break ;
			}
		}
		if (tmp && !tmp[i])
			break ;
	}
	return (free(str), tmp);
}
