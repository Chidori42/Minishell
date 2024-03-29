/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:55:14 by bramzil           #+#    #+#             */
/*   Updated: 2024/03/27 17:30:33 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_scape_spaces(char *input, int i)
{
	while (input[i] == 32 || (9 <= input[i] && \
			input[i] <= 13))
			i++;
	return (i);
}

static int	ft_scape_word(char *input, int i)
{
	while (input && input[i])
	{	
		if (input[i] == '\'' || input[i] == '\"')
			i = ft_scape_quotes(input, i);
		else if (input[i] == 32 || (9 <= input[i] && \
			input[i] <= 13))
			return (i);
		i++;
	}
	return (i);
}
static int	ft_word_len(char *input, int *i)
{
	int			l;

	*i = ft_scape_spaces(input, *i);
	l = *i;
	(*i)--;
	while (input && input[++(*i)])
	{
		if (input[*i] == '\'' || input[*i] == '\"')
			*i = ft_scape_quotes(input, *i);
		else if (input[*i] == 32 || (9 <= input[*i] && \
			input[*i] <= 13))
			break ;
	}
	return (*i - l);
}

static int	ft_count_words(char *input)
{
	int			i;
	int			nb;

	i = 0;
	nb = 0;
	while (input && input[i])
	{
		if (input [i] == 32 || (9 <= input[i] && \
			input[i] <= 13))
			i = ft_scape_spaces(input, i);
		else if (input[i] != 32 && (input[i] < 9 || \
			13 < input[i]))
		{
			i = ft_scape_word(input, i);
			nb++;
		}
		else if (input[i])
			i++;
	}
	return  (nb);
}

char	**ft_split_input(char *input)
{
	int			i;
	int			j;
	int			k;
	int			l_nb;
	int			wrd_len;
	char		**words;

	j = 0;
	k = 0;
	l_nb = ft_count_words(input);
	words = (char **)malloc(sizeof(char *) * (l_nb + 1));
	if (words)
	{
		i = -1;
		while (++i < l_nb)
		{
			k = ft_scape_spaces(input, k);
			wrd_len = ft_word_len(input, &j);
			words[i] = ft_substr(input, k, wrd_len);
			k += wrd_len;
		}
		words[l_nb] = NULL;
		ft_remove_quotes(words);
	}
	return (words);
}
