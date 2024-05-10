/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:55:14 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/10 03:35:57 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (!ft_strncmp(&input[i], "<STX>", 5))
			i = ft_scape_encapsule(input, i);
		if (input[i] == '\'' || input[i] == '\"')
			i = ft_scape_quotes(input, i);
		else if (input[i] == 32 || (9 <= input[i] && \
			input[i] <= 13))
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
		if (!ft_strncmp(&input[i], "<STX>", 5))
			i = ft_scape_encapsule(input, i);
		if (input[i] == '\'' || input[i] == '\"')
			i = ft_scape_quotes(input, i);
		else if (input[i] == 32 || (9 <= input[i] && \
			input[i] <= 13))
			break ;
		if (!input[i])
			break ;
		i++;
	}
	return (i - l);
}

int	ft_count_words(char *input)
{
	int			i;
	int			nb;

	i = 0;
	nb = 0;
	while (input && input[i])
	{
		if (!ft_strncmp(&input[i], "<STX>", 5))
			i = ft_scape_encapsule(input, i);
		else if (input [i] == 32 || (9 <= input[i] && \
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
	return (nb);
}

int	ft_split_input(char ***tab, char *input)
{
	int			t[2];
	int			l_nb;
	int			wrd_len;

	t[1] = 0;
	l_nb = ft_count_words(input);
	(*tab) = (char **)malloc(sizeof(char *) * (l_nb + 1));
	if (!(*tab))
		return (-1);
	t[0] = -1;
	while (++t[0] < l_nb)
	{
		t[1] = ft_scape_spaces(input, t[1]);
		wrd_len = ft_word_len(input, t[1]);
		(*tab)[t[0]] = ft_substr(input, t[1], wrd_len);
		if (!(*tab)[t[0]])
			return (ft_free_2_dm((*tab)), -1);
		t[1] += wrd_len;
	}
	(*tab)[l_nb] = NULL;
	return (0);
}
