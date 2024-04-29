/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 04:29:33 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/27 01:18:30 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_there_quotes(char *s)
{
	int			i;

	i = -1;
	while (s && s[++i])
		if (s[i] == '\'' || s[i] == '\"')
			return (1);
	return (0);
}

static void	ft_quotes_cpy(char *d, char *s, char qt, int *t)
{
	while (d && s && s[++t[0]])
	{
		if (s[t[0]] == qt)
			break ;
		else
		{
			d[t[1]] = s[t[0]];
			t[1]++;
		}
	}
}

static int	ft_count_qts(char *s)
{
	int			i;
	int			nb;

	i = -1;
	nb = 0;
	while (s && s[++i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			i = ft_scape_quotes(s, i);
			nb += 2;
		}
	}
	return (nb);
}

char	*ft_remove_qts(char *s)
{
	int			t[2];
	int			qts;
	char		*str;

	t[0] = -1;
	t[1] = 0;
	qts = ft_count_qts(s);
	str = (char *)malloc(sizeof(char) * \
		(ft_strlen(s) - qts + 1));
	if (str)
	{
		while (s && s[++t[0]])
		{
			if (s[t[0]] == '\'' || s[t[0]] == '\"')
				ft_quotes_cpy(str, s, s[t[0]], t);
			else
				str[t[1]++] = s[t[0]];
		}
		str[t[1]] = '\0';
	}
	free (s);
	return (str);
}

void	ft_remove_quotes(t_cmd *lst)
{
	int			i;
	t_cmd		*tmp;

	tmp = lst;
	while (tmp)
	{
		i = -1;
		while (tmp->data && tmp->data[++i])
			if (ft_is_there_quotes(tmp->data[i]))
				tmp->data[i] = ft_remove_qts(tmp->data[i]);
		i = -1;
		while (tmp->redir && tmp->redir[++i])
			if (ft_is_there_quotes(tmp->redir[i]))
				tmp->redir[i] = ft_remove_qts(tmp->redir[i]);
		tmp = tmp->next;
	}
}
