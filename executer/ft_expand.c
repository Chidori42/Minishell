/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 04:29:39 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/11 06:43:44 by bramzil          ###   ########.fr       */
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
	else
		value = ft_getenv(args->envp, ft_substr(tp, \
			(i + 1), len));
	if (en)
		(free(value), value = ft_encapsule(value));
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
		if (s[i] == '\"')
			dbq += 1;
		else if ((s[i] == '\'') && (dbq % 2) && fl)
			i = ft_scape_quotes(s, i);
		else if ((s[i] == '$') && (!i || \
			s[i - 1] != '\\') && \
			(0 <= varlen(s, (i + 1))))
			ref[i] = 'Y';
	}
	return (ref);
}

char	*ft_expand(t_pars *args, char *tp, char *rf, int en)
{
	int				i;
	int				len;
	char			*ptr;
	char			*value;

	i = -1;
	while (tp && rf && tp[++i])
	{
		if ((tp[i] == '$') && (rf[i] == 'Y'))
		{
			len = varlen(tp, (i + 1));
			value = ft_get_value(args, tp, en, i);
			(ptr = ft_substr(tp, (i + len + 1), \
				(ft_strlen(tp) - (i + 1))), free(tp));
			tp = ft_strs_join(ft_substr(tp, 0, i), \
				ft_strdup(value));
			tp = ft_strs_join(tp, ptr);
			ptr = ft_substr(rf, (i + len + 1), \
				(ft_strlen(rf) - (i + 1)));
			(free(rf), rf = ft_strs_join(ft_substr(rf, \
				0, i), value));
			(rf = ft_strs_join(rf, ptr), i++);
		}
	}
	return (free(rf), tp);
}