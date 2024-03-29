/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:28:37 by bramzil           #+#    #+#             */
/*   Updated: 2024/02/21 15:37:35 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wrdlen(char const *s, char c)
{
	size_t				wrd_len;

	wrd_len = 0;
	while (*s && (*s != c) && ++wrd_len)
		s++;
	return (wrd_len);
}

static void	ft_free_mem(char **strs)
{
	size_t			i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		strs[i] = 0;
		i++;
	}
	free (strs);
	strs = 0;
}

static size_t	ft_count_words(char const *s, char c)
{
	size_t				count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char			**strs;
	char			**ref;

	if (!s)
		return (0);
	strs = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!strs)
		return (0);
	ref = strs;
	while (*s)
	{
		while (*s && (*s == c))
			s++;
		if (!(*s))
			break ;
		*strs = ft_substr(s, 0, ft_wrdlen(s, c));
		if (!(*strs++))
		{
			ft_free_mem(ref);
			return (0);
		}
		s += ft_wrdlen(s, c);
	}
	*strs = 0;
	return (ref);
}
