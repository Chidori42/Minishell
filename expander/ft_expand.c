/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 04:29:39 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/14 19:40:47 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_inject_value(char **wrd, char *vl, int ln, int i)
{
	char		*tmp;

	tmp = ft_strs_join(ft_substr((*wrd), 0, i), \
		ft_strdup(vl));
	if (!tmp)
		return (-1);
	tmp = ft_strs_join(tmp, ft_substr((*wrd), (i + ln + 1), \
		(ft_strlen((*wrd)) - (i + ln + 1))));
	if (!tmp)
		return (-1);
	(free((*wrd)), (*wrd) = tmp);
	return (0);
}

static int	varlen(char *s, int i)
{
	int			len;

	len = 0;
	if (!s || (!ft_isalnum(s[i]) && (s[i] != '\'') && \
		(s[i] != '\"') && (s[i] != '?') && (s[i] != '_')))
		return (-1);
	else if (s)
	{
		if (ft_isdigit(s[i]) || s[i] == '?')
			return (1);
		while (s && s[i] && (ft_isalnum(s[i]) || \
			(s[i] == '_')) && ++len)
			i++;
	}
	return (len);
}

static char	*ft_get_value(t_pars *args, char *tp, int en, int i)
{
	int			len;
	char		*value;

	value = NULL;
	len = varlen(tp, (i + 1));
	if (tp[i + 1] == '?')
		(value = ft_itoa(args->ext_st));
	else if (0 < len)
		value = ft_getenv(args->envp, ft_substr(tp, \
			(i + 1), len));
	if (en && value)
		value = ft_encapsule(value);
	return (value);
}

char	*ft_expand_it(char *s, int fl)
{
	int			i;
	int			dbq;
	char		*ref;

	i = -1;
	dbq = 3;
	ref = ft_strdup(s);
	while (s && ref && s[++i])
	{
		if (s[i] == '\"' && (!i || (s[i - 1] != '\\')))
			dbq += 1;
		else if ((s[i] == '\'') && (dbq % 2) && fl)
			i = ft_scape_quotes(s, i);
		else if ((s[i] == '$') && ((s[i + 1] == '\"') || \
			(s[i + 1] == '\'')))
			((dbq % 2) && (ref[i] = 'Y'));
		else if ((s[i] == '$') && (0 <= varlen(s, (i + 1))))
			ref[i] = 'Y';
		if (!s[i])
			break ;
	}
	return (ref);
}

char	*ft_expand(t_pars *args, char *tp, char *rf, int en)
{
	int				i;
	int				len;
	char			*value;

	i = -1;
	while (tp && rf && tp[++i])
	{
		if ((tp[i] == '$') && (rf[i] == 'Y'))
		{
			len = varlen(tp, (i + 1));
			value = ft_get_value(args, tp, en, i);
			if (ft_inject_value(&tp, value, len, i) || \
				ft_inject_value(&rf, value, len, i))
				return (free(rf), free(value), \
					free(tp), NULL);
			free(value);
		}
		if (!tp[i])
			break ;
	}
	return (free(rf), tp);
}
