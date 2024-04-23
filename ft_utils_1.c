/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:31:58 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/23 18:23:40 by bramzil          ###   ########.fr       */
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

int	ft_dup_fd(int new, int old)
{
	if (dup2(new, old) < 0)
		return (ft_putendl_fd(strerror(errno), 2), -1);
	return (0);
}

int	ft_is_builtin(char **tab)
{
	char		*ref;
	char		*ref_1;

	ref = "cd unset exit";
	ref_1 = "echo pwd env";
	if (tab)
	{
		if (!ft_strcmp(tab[0], "export") && tab[1])
			return (2);
		else if (ft_strnstr(ref_1, tab[0], ft_strlen(ref_1)) || \
			!ft_strcmp(tab[0], "export"))
			return (1);
		else if (tab[0] && ft_strnstr(ref, tab[0], ft_strlen(ref)))
			return (2);
	}
	return (0);
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