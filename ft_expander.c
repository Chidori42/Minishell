/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:40:45 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/04 23:32:55 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_len(char *s, int i)
{
	int			len;

	len = 0;
	if (s)
	{
		if (ft_isdigit(s[i]) || s[0] == '?')
			return (1);
		while (s && s[i] && (ft_isalnum(s[i]) || \
			(s[i] == '_') || (s[i] == '\"')) && ++len)
			i++;
	}
	return (len);
}

static int	ft_expansion(char *s, int i)
{
	while (s && s[++i])
	{
		if (s[i] == '\'')
			i = ft_scape_quotes(s, i);
		else if (s[i] && (s[i] == '\"'))
		{
			while (s[i] && s[++i] && (s[i] != '\"'))
				if ((s[i] == '$') && var_len(&s[i + 1], 0))
					return (i);
		}
		else if (s[i] && (s[i] == '$') && var_len(&s[i + 1], 0))
			return (i);
		if (!s[i])
			break ;
	}
	return (-1);
}

static char	*ft_expand(t_pars *args, char *s, int ind, int len)
{
	char		*tmp;
	char		*ptr;
	char		*value;

	ptr = s;
	if (!args || !s)
		return (NULL);
	tmp = ft_substr(s, (ind + 1), len);
	if (!tmp)
		return (NULL);
	value = tmp;
	tmp = ft_strtrim(tmp, "\"");
	free(value);
	if (!ft_strcmp(tmp, "?"))
		value = ft_itoa(ft_get_status(0, 0, 0));
	else
		value = ft_getenv(args->envp, tmp);
	if (!ft_strcmp(tmp, "PATH") && !value)
		value = ft_strdup(args->path);
	ptr = ft_strs_join(ft_substr(s, 0, ind), \
		ft_strdup(value));
	ptr = ft_strs_join(ptr, ft_substr(s, \
		(ind + len + 1), (ft_strlen(s) - (ind + len))));
	free (s);
	return (free(value), free(tmp), ptr);
}

int	ft_expander(t_pars *args, char **tab)
{
	int			i;
	int			ind;
	int			len;
	char		*tmp;

	i = -1;
	while (tab && tab[++i])
	{
		ind = -1;
		ind = ft_expansion(tab[i], ind);
		if (0 <= ind)
		{
			tmp = tab[i];
			len = var_len(&tmp[ind + 1], 0);
			tab[i] = ft_expand(args, tmp, ind, len);
			if (!tab[i])
				return (-1);
			i--;
		}
	}
	return (0);
}
