/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 04:29:33 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/14 19:42:42 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_there_quotes(char *s)
{
	int			i;

	i = -1;
	while (s && s[++i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && \
			(!i || s[i - 1] != '\\'))
			return (1);
	}
	return (0);
}

static void	ft_quotes_cpy(char *d, char *s, char qt, int *t)
{
	while (d && s && s[++t[0]])
	{
		if (s[t[0]] == qt && \
			(!t[0] || s[t[0] - 1] != '\\'))
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
	int			rf;
	char		qt;

	nb = 0;
	i = -1;
	while (s && s[++i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && \
			(!i || s[i - 1] != '\\'))
		{
			rf = i;
			nb += 1;
			qt = s[i];
			i = ft_scape_quotes(s, i);
			if (rf != i && s[i] == qt)
				nb += 1;
		}
		if (!s[i])
			break ;
	}
	return (nb);
}

char	*ft_remove_qts(char *s)
{
	int			t[2];
	int			qts;
	char		*str;

	t[0] = 0;
	t[1] = 0;
	qts = ft_count_qts(s);
	str = (char *)malloc(sizeof(char) * \
		(ft_strlen(s) - qts + 1));
	if (str)
	{
		while (s && s[t[0]])
		{
			if ((s[t[0]] == '\'' || s[t[0]] == '\"') && \
				(!t[0] || s[t[0] - 1] != '\\'))
				ft_quotes_cpy(str, s, s[t[0]], t);
			else
				str[t[1]++] = s[t[0]];
			if (s[t[0]])
				t[0]++;
		}
		str[t[1]] = '\0';
	}
	return (free(s), str);
}

int	ft_remove_quotes(t_cmd *lst)
{
	int			t[2];
	char		*ptr;
	char		**tab;
	t_cmd		*tmp;

	t[1] = 0;
	tmp = lst;
	while (tmp)
	{
		t[0] = -1;
		(t[1] && (tab = tmp->redir));
		(!t[1] && (++t[1]) && (tab = tmp->data));
		while (tab && tab[++t[0]])
		{
			if (ft_is_there_quotes(tab[t[0]]))
			{
				ptr = ft_remove_qts(ft_strdup(tab[t[0]]));
				if (ptr)
					(free(tab[t[0]]), tab[t[0]] = ptr);
			}
		}
		if ((tab == tmp->redir) && t[1]--)
			tmp = tmp->next;
	}
	return (0);
}
