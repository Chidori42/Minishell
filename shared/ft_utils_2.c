/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 03:34:22 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/05/06 03:36:44 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_arg(t_pars *args, t_cmd *node, char **tab, int f)
{
	int			i;
	char		**tmp_1;

	i = -1;
	tmp_1 = ft_split("export _=", ' ');
	while (tmp_1 && tab && tab[++i])
	{
		if (!tab[i + 1])
		{
			if (f == 1)
				tmp_1[1] = ft_strs_join(tmp_1[1], \
					ft_strdup(tab[i]));
			ft_export(args, node, tmp_1);
		}
	}
	return (ft_free_2_dm(tmp_1), 0);
}

int	ft_is_builtin(char **tab)
{
	char		*ref;

	ref = "cd unset exit env pwd echo export";
	if (tab && tab[0])
	{
		if (ft_strstr(ref, tab[0]) || \
			!ft_strcmp(tab[0], "export"))
			return (1);
	}
	return (0);
}

int	ft_strcmp(char *s_1, char *s_2)
{
	int			i;

	i = 0;
	if (!s_1 || !s_2)
		return (-1);
	while (s_1[i] && s_2[i] && (s_1[i] == s_2[i]))
		i++;
	return (s_1[i] - s_2[i]);
}

char	*ft_getenv(char **envp, char *name)
{
	int			i;
	char		*vl;
	char		*var;

	i = -1;
	while (envp && name && envp[++i])
	{
		var = ft_substr(envp[i], 0, \
			ft_var_len(envp[i]));
		if (!ft_strcmp(var, name))
		{
			vl = ft_substr(envp[i], (ft_strlen(var) + 1), \
				ft_strlen(envp[i]));
			free(var);
			return (vl);
		}
		free(var);
	}
	return (NULL);
}

int	ft_resplit_input(char ***tab)
{
	int				i;
	char			*tmp;
	char			**tmp_1;

	i = -1;
	tmp = NULL;
	if (!tab || !(*tab))
		return (0);
	tmp_1 = (*tab);
	while ((*tab) && (*tab)[++i])
	{
		tmp = ft_strs_join(tmp, ft_strdup(" "));
		if (!tmp)
			return (-1);
		tmp = ft_strs_join(tmp, (*tab)[i]);
		if (!tmp)
			return (-1);
	}
	ft_split_input(tab, tmp);
	return (free(tmp_1), free(tmp), 0);
}
