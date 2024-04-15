/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:40:45 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/15 16:16:36 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_valid(char c)
{
	if (c < 9 || ((13 < c) && (c != 32) && \
		(c != '\'') && (c != '\"')))
		return (1);
	return (0);
}

int	ft_word_len(char *s, int i)
{
	int			len;

	len = 0;
	while (s && s[++i] && (s[i] < 9 || \
		(13 < s[i] && s[i] != 32)) && \
		(s[i] != '\'') && (s[i] != '\"'))
		len++;
	return (len);
}

static char	*ft_expand(char *s, int ind, int len)
{
	char		*tmp;
	char		*ptr;
	char		*value;

	ptr = s;
	tmp = ft_substr(s, (ind + 1), len);
	value = getenv(tmp);
	ptr = ft_strs_join(ft_substr(s, 0, ind), \
		ft_strdup(value));
	ptr = ft_strs_join(ptr, ft_substr(s, \
		(ind + len + 1), (ft_strlen(s) - (ind + len))));
	free (s);
	return (free(tmp), ptr);
}

static int	ft_expansion(char *s, int i)
{
	while (s && s[++i])
	{
		if (s[i] == '\'')
			i = ft_scape_quotes(s, i);
		else if (s[i] == '\"')
		{
			while (s[++i] && s[i] != '\"')
				if (s[i] == '$' && ft_is_valid(s[i + 1]))
					return (i);
		}
		else if (s[i] == '$' && ft_is_valid(s[i + 1]))
			return (i);
		if (!s[i])
			break ;
	}
	return (-1);
}

void	ft_expander(char **tab)
{
	int			i;
	int			ind;
	int			len;
	char		*tmp;

	i = -1;
	ind = 0;
	while (tab && tab[++i])
	{
		ind = ft_expansion(tab[i], ind);
		if (0 <= ind)
		{
			tmp = tab[i];
			len = ft_word_len(tmp, ind);
			tab[i] = ft_expand(tmp, ind, len);
			i--;
		}
	}
}
