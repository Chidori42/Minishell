/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:40:45 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/25 01:29:22 by bramzil          ###   ########.fr       */
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
			s[i] == '_') && ++i)
			len++;
	}
	return (len);
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
				if (s[i] == '$' && var_len(&s[i + 1], i))
					return (i);
		}
		else if (s[i] == '$' && var_len(&s[i + 1], i))
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
	if (!ft_strcmp(tmp, "?"))
		value = ft_itoa(args->ext_st);
	else
		value = ft_getenv(args->envp, tmp);
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
			len = var_len(&tmp[ind + 1], ind);
			printf("from expand: %s| len %d\n", tab[i], len);
			tab[i] = ft_expand(args, tmp, ind, len);
			if (!tab[i])
				return (-1);
			i--;
		}
	}
	return (0);
}
