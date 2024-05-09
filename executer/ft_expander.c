/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:06:10 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/09 04:23:20 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	varlen(char *s, int i)
{
	int			len;

	len = 0;
	if (!s || (!ft_isalnum(s[i]) && (s[i] != '\'') && \
		(s[i] != '\"') && (s[i] != '?') && (s[i] != '_')))
		return (-1);
	else if (s)
	{
		if (ft_isdigit(s[i]) || s[0] == '?')
			return (1);
		while (s && s[i] && (ft_isalnum(s[i]) || \
			(s[i] == '_')) && ++len)
			i++;
	}
	return (len);
}

static char	*ft_expand_it(char *s)
{
	int			i;
	int			dbq;
	char		*ref;
	
	i = -1;
	dbq = 3;
	ref = ft_strdup(s);
	while (s && ref && s[++i])
	{
		if (s[i] == '\"')
			dbq += 1;
		else if ((s[i] == '\'') && (dbq % 2))
			i = ft_scape_quotes(s, i);
		else if ((s[i] == '$') && (!i || s[i - 1] != '\\') && \
			(0 <= varlen(s, (i + 1))))
			ref[i] = 'Y';
	}
	return (ref);
}

static char	*ft_expand(t_pars *args, char *tmp, char *ref)
{
	int				i;
	int				len;
	char			*ptr;
	char			*value;

	i = -1;
	while (tmp && ref && tmp[++i])
	{
		if ((tmp[i] == '$') && (ref[i] == 'Y'))
		{
			len = varlen(tmp, (i + 1));
			if (tmp[i + 1] == '?')
				(value = ft_itoa(args->ext_st), (len = 1));
			else
				value = ft_getenv(args->envp, ft_substr(tmp, (i + 1), len));
			ptr = ft_substr(tmp, (i + len + 1), (ft_strlen(tmp) - (i + 1)));
			free(tmp);
			tmp = ft_strs_join(ft_substr(tmp, 0, i), ft_strdup(value));
			tmp = ft_strs_join(tmp, ptr);
			ptr = ft_substr(ref, (i + len + 1), (ft_strlen(ref) - (i + 1)));
			(free(ref), ref = ft_strs_join(ft_substr(ref, 0, i), value));
			(ref = ft_strs_join(ref, ptr), i++);
		}
	}
	return (free(ref), tmp);
}

int	ft_expander(t_pars *args, char **tab)
{
	int			i;
	char		*tmp;
	char		*ref;
	char		*new;

	i = -1;
	while (tab && tab[++i])
	{
		ref = ft_expand_it(tab[i]);
		tmp = ft_remove_qts(ft_strdup(tab[i]));
		ref = ft_remove_qts(ref);
		new = ft_expand(args, tmp, ref);
		if (new)
			(free(tab[i]), (tab[i] = new));
	}
	return (0);
}