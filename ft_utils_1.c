/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:31:58 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/28 00:43:37 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_dup_fd(int new, int old)
{
	if ((2 < new) && dup2(new, old) < 0)
		return (ft_putendl_fd(strerror(errno), 2), -1);
	return (0);
}

int	ft_get_exit_status(int new, int set)
{
	int				tmp;
	static int		old;

	tmp = old;
	if (set)
		old = new;
	return (tmp);
}

void	ft_parse_error(char *str)
{
	write(2, "parse error near `", 18);
	write(2, str, ft_strlen(str));
	write(2, "'\n", 2);
	free (str);
	ft_get_exit_status(258, 1);
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

int	ft_set_last_arg(t_pars *args, char **tab)
{
	int			i;
	char		**tmp_1;

	i = -1;
	if (!args || !tab || !tab[0])
		return (0);
	tmp_1 = (char **)malloc(sizeof(char *) * 3);
	if (!tmp_1)
		return (-1);
	tmp_1[0] = ft_strdup("export");
	if (!tmp_1[0])
		return (ft_free_2_dm(tmp_1), -1);
	tmp_1[2] = NULL;
	while (tab && tab[++i])
	{
		if (!tab[i + 1])
		{
			tmp_1[1] = ft_strjoin("_=", tab[i]);
			if (!tmp_1[1])
				return (ft_free_2_dm(tmp_1), -1);
			ft_export(args, tmp_1);
		}
	}
	return (ft_free_2_dm(tmp_1), 0);
}

int	ft_is_builtin(char **tab)
{
	char		*ref;
	char		*ref_1;

	ref = "cd unset exit";
	ref_1 = "env pwd echo";
	if (tab && tab[0])
	{
		if (!ft_strcmp(tab[0], "export") && tab[1])
			return (2);
		else if (ft_strstr(ref_1, tab[0]) || \
			!ft_strcmp(tab[0], "export"))
			return (1);
		else if (tab[0] && ft_strstr(ref, tab[0]))
			return (2);
	}
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

char	*ft_getenv(char **envp, char *name)
{
	int			i;
	char		*vl;
	char		**var;

	i = -1;
	while (envp && name && envp[++i])
	{
		var = ft_split(envp[i], '=');
		if (!ft_strcmp(var[0], name))
		{
			vl = ft_strdup(var[1]);
			ft_free_2_dm(var);
			return (vl);
		}
		ft_free_2_dm(var);
	}
	return (NULL);
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

int	ft_strstr(char *ref, char *s)
{
	int			i;
	char		**tab;

	i = -1;
	tab = NULL;
	if (ref && s)
	{
		tab = ft_split(ref, ' ');
		if (!tab)
			return (0);
		while (tab[++i])
			if (!ft_strcmp(tab[i], s))
				return (ft_free_2_dm(tab), 1);
	}
	return (ft_free_2_dm(tab), 0);
}

static int	ft_redir_error(char *s)
{
	char		*tmp;

	tmp = ft_strs_join(ft_strdup(s), \
		ft_strdup(": ambiguous redirect"));
	if (!tmp)
		return (-1);
	ft_putendl_fd(tmp, 2);
	return (free(tmp), -1);
}

int	ft_redir_expand(t_pars *args, char ***redir)
{
	int			i;
	char		**tmp;

	i = -1;
	tmp = (char **)malloc(sizeof(char *) * 2);
	if (!tmp)
		return (-1);
	tmp[1] = NULL;
	while ((*redir) && (*redir)[++i])
	{
		tmp[0] = ft_strdup((*redir)[i]);
		if (!tmp[0])
			return (free(tmp), -1);
		if (!ft_expander(args, tmp))
		{
			if ((1 != ft_count_words(tmp[0])))
				return (ft_free_2_dm(tmp), \
					ft_redir_error((*redir)[i]));
			free((*redir)[i]);
			(*redir)[i] = tmp[0];
		}
	}
	return (free(tmp), 0);
}
