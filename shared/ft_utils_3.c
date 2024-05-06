/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 03:35:50 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/05/06 16:44:59 by bramzil          ###   ########.fr       */
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

static int	ft_redir_error(char *s)
{
	char		*tmp;

	ft_get_status(0, NULL, 1, 2);
	tmp = ft_strs_join(ft_strdup(s), \
		ft_strdup(": ambiguous redirect"));
	if (!tmp)
		return (-1);
	ft_putendl_fd(tmp, 2);
	return (free(tmp), -1);
}

int	ft_redir_expand(t_pars *args, char ***redir)
{
	int			i;
	char		**tmp;

	i = -1;
	tmp = (char **)malloc(sizeof(char *) * 2);
	if (!tmp)
		return (-1);
	tmp[1] = NULL;
	while ((*redir) && (*redir)[++i])
	{
		tmp[0] = ft_strdup((*redir)[i]);
		if (!tmp[0])
			return (free(tmp), -1);
		if (!ft_expander(args, tmp))
		{
			if ((1 != ft_count_words(tmp[0])))
				return (ft_free_2_dm(tmp), \
					ft_redir_error((*redir)[i]));
			free((*redir)[i]);
			(*redir)[i] = tmp[0];
		}
	}
	return (free(tmp), 0);
}
