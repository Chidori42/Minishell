/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:31:58 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/07 21:11:03 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free_2_dm(char **arr)
{
	int			i;

	i = -1;
	while (arr && arr[++i])
		free (arr[i]);
	free (arr);
	return (0);
}

int	ft_strcmp(char *s_1, char *s_2)
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
	write(2, "parse error near `", 18);
	write(2, str, ft_strlen(str));
	write(2, "'\n", 2);
	free (str);
}

char	*ft_strs_join(char *s1, char *s2)
{
	char		*str;

	str = NULL;
	if (!s1 && s2)
		str = ft_strdup(s2);
	else if (s1 && !s2)
		str = ft_strdup(s1);
	else if (s1 && s2)
		str = ft_strjoin(s1, s2);
	return(str);
	//return (free (s1), free (s2), str);
}

static int	ft_redir_nbr(char **tab, int i)
{
	int			nb;

	nb = 0;
	while (tab && tab[i] && ft_strcmp(tab[i], "|"))
	{
		if (ft_is_redir(tab[i]))
			nb += 2;
		i++;
	}
	return (nb);
}

char	**ft_get_redir(char **tab, int i)
{
	int			j;
	int			rdr_nbr;
	char		**std;

	j = -1;
	std = NULL;
	rdr_nbr = ft_redir_nbr(tab, i);
	std = (char **)malloc(sizeof(char *) * (rdr_nbr + 1));
	while (std && tab && tab[i] && \
		ft_strcmp(tab[i], "|"))
	{
		if (ft_is_redir(tab[i]))
		{
			std[++j] = ft_strdup(tab[i]);
			std[++j] = ft_strdup(tab[++i]);
		}
		i++;
	}
	std[++j] = NULL;
	return (std);
}
