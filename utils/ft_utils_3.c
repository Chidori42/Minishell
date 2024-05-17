/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 03:35:50 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/05/13 19:08:30 by ael-fagr         ###   ########.fr       */
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

int	ft_redir_error(char *s)
{
	char		*tmp;

	ft_get_status(0, NULL, 1, 2);
	tmp = ft_strs_join(ft_strdup(s), \
		ft_strdup(": ambiguous redirect"));
	if (tmp)
		ft_putendl_fd(tmp, 2);
	return (free(tmp), 1);
}

char	*ft_encapsule(char *str)
{
	char		*tmp;

	tmp = ft_strdup(str);
	if (!tmp)
		return (free(str), NULL);
	tmp = ft_strs_join(ft_strdup("\'"), tmp);
	if (!tmp)
		return (free(str), NULL);
	tmp = ft_strs_join(tmp, ft_strdup("\'"));
	if (!tmp)
		return (free(str), NULL);
	return (free(str), tmp);
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
