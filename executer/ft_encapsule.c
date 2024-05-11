/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_encapsule.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 00:32:57 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/11 00:50:08 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_copy_encapsule(char *d, char *s, int *t)
{
	int			end;
	
	end = ft_scape_encapsule(s, t[0]);
	while (s[t[0]] && t[0] <= end)
	{	
		d[t[1]] = s[t[0]];
		(t[1]++, t[0]++);
	}
}

int	ft_scape_encapsule(char *str, int i)
{
	int		ref;

	ref = i + 1;
	while (str && str[++i])
		if (!ft_strncmp(&str[i], "<ETX>", 5))
			return (i + 4);
	return (ref);
}

int	ft_encapsule_or(char *cmd, char *str, char *ref)
{
	int		i;
	int		rt;

	i = -1;
	rt = 0;
	if (ft_strcmp(cmd, "export"))
		return (1);
	while (str && ref && str[++i])
	{
		if (str[i] == '=')
			return (rt);
		else if ((str[i] == '$') && (ref[i] == 'Y'))
			rt++;
	}
	return (0);
}

char    *ft_encapsule(char *str)
{
	char		*tmp;

	tmp = ft_strdup(str);
	if (tmp)
	{
		tmp = ft_strs_join(ft_strdup("<STX>"), tmp);
		tmp = ft_strs_join(tmp, ft_strdup("<ETX>"));
	}
	return (tmp);
}
