/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resplit_tok.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:42:24 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/09 19:54:19 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_scape_spaces(char *str, int i)
{
	while (str[i] && (str[i] == 32))
		i++;
	return (i);
}

static char	*ft_join_tab(char **tab)
{
	int			i;
	char		*str;

	i = -1;
	str = NULL;
	while (tab && tab[++i])
	{
		str = ft_strs_join(str, ft_strdup(" "));
		str = ft_strs_join(str, ft_strdup(tab[i]));
	}
	return (str);
}

static int	ft_scape_word(char *input, int i)
{
	while (input && input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = ft_scape_quotes(input, i);
		else if (input[i] == 32)
			return (i);
		if (input[i])
			i++;
	}
	return (i);
}

static	int	ft_word_len(char *input, int i)
{
	int			l;

	l = i;
	while (input && input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = ft_scape_quotes(input, i);
		else if (input[i] == 32)
			break ;
		if (!input[i])
			break ;
		i++;
	}
	return (i - l);
}

static int	ft_count_word(char *input)
{
	int			i;
	int			nb;

	i = 0;
	nb = 0;
	if (!input)
		return (-1);
	while (input && input[i])
	{
		while (input[i] && (input[i] == 32))
			i++;
		if (input[i] && input[i] != 32)
		{
			i = ft_scape_word(input, i);
			nb++;
		}
		else if (input[i])
			i++;
	}
	return (nb);
}

int	ft_resplit_tok(char ***tab)
{
	int			t[2];
	int			w_nb;
	char		*str;
	int			wrd_len;

	t[1] = 0;
	str = ft_join_tab(*tab);
	w_nb = ft_count_word(str);
	(ft_free_2_dm((*tab)), t[0] = -1);
	(*tab) = (char **)malloc(sizeof(char *) * (w_nb + 1));
	if (!(*tab))
		return (free(str), -1);
	while (++t[0] < w_nb)
	{
		t[1] = ft_scape_spaces(str, t[1]);
		wrd_len = ft_word_len(str, t[1]);
		(*tab)[t[0]] = ft_substr(str, t[1], wrd_len);
		if (!(*tab)[t[0]])
			return (ft_free_2_dm((*tab)), free(str), -1);
		t[1] += wrd_len;
	}
	(*tab)[w_nb] = NULL;
	return (free(str), 0);
}
