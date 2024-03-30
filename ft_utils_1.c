/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:31:58 by bramzil           #+#    #+#             */
/*   Updated: 2024/03/29 22:25:08 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free_2_dm(char **arr)
{
	int			i;

	i = -1;
	while (arr[++i])
		free (arr[i]);
	free (arr);
	return (0);
}

int 	ft_strcmp(char *s_1, char *s_2)
{
	int			i;

	i = 0;
	if (s_1 && !s_2)
		return (1);
	else if (!s_1 && s_2)
		return (-1);
	while (s_1[i] && s_2[i] && s_1[i] == s_2[i])
		i++;
	return (s_1[i] - s_2[i]);
}

void	ft_parse_error(char *str)
{
	write(1, "parse error near `", 18);
	write(1, str, ft_strlen(str));
	write(1, "'\n", 2);
	free (str);
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

char	*ft_get_redir(char **tab, int i)
{
    char		*std;

    std = NULL;
    while (tab && tab[i] && \
		ft_strcmp(tab[i], "|"))
    {
		if (!ft_strcmp("<", tab[i]) || \
			!ft_strcmp(">", tab[i]) || \
			!ft_strcmp(">>", tab[i]))
		{
			std = ft_strs_join(std, ft_strdup(tab[i]));
			std = ft_strs_join(std, ft_strdup(" "));
			std = ft_strs_join(std, ft_strdup(tab[i + 1]));
			std = ft_strs_join(std, ft_strdup(" "));
		}
		i++;
    }
    return (std);
}