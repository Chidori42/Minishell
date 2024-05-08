/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_backslash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 04:43:00 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/05/08 04:43:41 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_inject_back_slach(char **new, int *i)
{
	char		*tmp;

	tmp = (*new);
	(*new) = ft_substr((*new), 0, (*i));
	(*new) = ft_strs_join((*new), ft_strdup("\\"));
	(*new) = ft_strs_join((*new), ft_substr(tmp, (*i), \
		(ft_strlen(tmp) - (*i))));
	(free(tmp), (*i)++);
}

char	*ft_add_back_slash(char *str)
{
	int			i;
	int			b;
	char		*new;

	b = 0;
	i = 0;
	new = ft_strdup(str);
	while (new && new[i])
	{
		if (new[i] == '=')
			b = 1;
		else if (new[i] == '\'')
			i = ft_scape_quotes(new, i);
		else if ((new[i] == '$') && b)
			ft_inject_back_slach(&new, &i);
		if (new && new[i])
			i++;
	}
	if (new)
		return (free(str), new);
	return (str);
}