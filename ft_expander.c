/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:40:45 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/21 20:41:26 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_word_len(char *s, int i)
{
	int			len;

	len = 0;
	if (ft_isdigit(s[i]))
		return (1);
	while (s && s[i] && (ft_isalnum(s[i]) || \
		s[i] == '_') && ++i)
		len++;
	return (len);
}

static int	ft_is_identifier(char *id)
{
	int			i;
	int			l;

	i = -1;
	l = ft_word_len(id, 0);
	if (0 < l)
		return (1);
	return (0);
}

static char	*ft_expand(t_pars *args, char *s, int ind, int len)
{
	char		*tmp;
	char		*ptr;
	char		*value;

	ptr = s;
	tmp = ft_substr(s, (ind + 1), len);
	value = ft_getenv(args->envp, tmp);
	ptr = ft_strs_join(ft_substr(s, 0, ind), \
		ft_strdup(value));
	ptr = ft_strs_join(ptr, ft_substr(s, \
		(ind + len + 1), (ft_strlen(s) - (ind + len))));
	free (s);
	return (free(value), free(tmp), ptr);
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
				if (s[i] == '$' && ft_is_identifier(&s[i + 1]))
					return (i);
		}
		else if (s[i] == '$' && ft_is_identifier(&s[i + 1]))
			return (i);
		if (!s[i])
			break ;
	}
	return (-1);
}

int	ft_expander(t_pars *args, char **tab)
{
	int			i;
	int			j;
	int			ind;
	int			len;
	char		*tmp;
	
	j = 0;
	i = -1;
	while (tab && tab[++i])
	{
		ind = -1;
		ind = ft_expansion(tab[i], ind);
		if (0 <= ind && ++j)
		{
			tmp = tab[i];
			len = ft_word_len(tmp, (ind + 1));
			tab[i] = ft_expand(args, tmp, ind, len);
			i--;
		}
	}
	return (j);
}
