/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resplit_tok.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:42:24 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/09 20:12:59 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_resplit_tok(char ***tab)
{
	char		*str;

	str = ft_join_tab(*tab);
	ft_split_input(tab, str);
	return (free(str), 0);
}
