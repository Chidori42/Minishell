/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 03:35:50 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/05/12 01:55:11 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free_2_dm(char **arr)
{
	int			i;

	i = -1;
	while (arr && arr[++i])
		free (arr[i]);
	free (arr);
	return (0);
}

char	*ft_strs_join(char *s1, char *s2)
{
	char		*str;

	str = NULL;
	if (!s1 && s2)
		str = ft_strdup(s2);
	else if (s1 && !s2)
		str = ft_strdup(s1);
	else if (s1 && s2)
		str = ft_strjoin(s1, s2);
	return (free (s1), free (s2), str);
}

int	ft_strstr(char *ref, char *s)
{
	int			i;
	char		**tab;

	i = -1;
	tab = NULL;
	if (ref && s)
	{
		tab = ft_split(ref, ' ');
		if (!tab)
			return (0);
		while (tab[++i])
			if (!ft_strcmp(tab[i], s))
				return (ft_free_2_dm(tab), 1);
	}
	return (ft_free_2_dm(tab), 0);
}

char	*ft_encapsule(char *str)
{
	char		*tmp;

	tmp = ft_strdup(str);
	if (str)
	{
		tmp = ft_strs_join(ft_strdup("\'"), tmp);
		tmp = ft_strs_join(tmp, ft_strdup("\'"));
	}
	return (tmp);
}

int	ft_encapsule_or(char *cmd, char *str, char *ref)
{
	int		i;
	int		rt;

	i = -1;
	rt = 1;
	if (!ft_strcmp(cmd, "export"))
	{
		while (str && ref && str[++i])
		{
			if ((str[i] == '$') && (ref[i] == 'Y'))
				rt = 0;
			else if (str[i] == '=')
				return (rt);
		}
	}
	return (0);
}
