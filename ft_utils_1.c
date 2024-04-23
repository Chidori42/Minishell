/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:31:58 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/23 03:58:04 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_error(char *str)
{
	write(2, "parse error near `", 18);
	write(2, str, ft_strlen(str));
	write(2, "'\n", 2);
	free (str);
}

int	ft_free_2_dm(char **arr)
{
	int			i;

	i = -1;
	while (arr && arr[++i])
		free (arr[i]);
	free (arr);
	return (0);
}

int 	ft_strcmp(char *s_1, char *s_2)
{
	int			i;

	i = 0;
	if (!s_1 || !s_2)
		return (-1);
	while (s_1[i] && s_2[i] && (s_1[i] == s_2[i]))
		i++;
	return (s_1[i] - s_2[i]);
}

char 	*ft_strs_join(char *s1, char *s2)
{
	char		*str;

	str = NULL;
	if (!s1 && s2)
		str = ft_strdup(s2);
	else if (s1 && !s2)
		str = ft_strdup(s1);
	else if (s1 && s2)
		str = ft_strjoin(s1, s2);
	return (free (s1), free (s2), str);
}
char **ft_resplit_input(char **tab)
{
	int				i;
	char			*tmp;

	i = -1;
	tmp = NULL;
	while (tab && tab[++i])
	{
		tmp = ft_strs_join(tmp, ft_strdup(" "));
		tmp = ft_strs_join(tmp, tab[i]);
	}
	free (tab);
	return (ft_split_input(tmp));
}