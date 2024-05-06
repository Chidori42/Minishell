/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:31:58 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/05 12:12:57 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_dup_fd(int new, int old)
{
	if ((2 < new) && dup2(new, old) < 0)
		return (ft_putendl_fd(strerror(errno), 2), -1);
	return (0);
}

int ft_close(t_pars *args)
{
	ft_free_2_dm(args->envp);
	printf("\033[AMinishell: exit\n");
	exit(0);
}

char	**ft_split_fr(char *str, char c)
{
	char		**arr;

	arr = NULL;
	if (str)
		arr = ft_split(str, c);
	return (free(str), arr);
}

int	ft_get_status(pid_t new_pid, int new, int set)
{
	int				tmp;
	static int		old;
	static pid_t	old_pid;

	tmp = old;
	if (set == 100)
		old_pid = 0;
	else if (set && ((old_pid <= new_pid) || \
		(new_pid == 0)))
	{
		old_pid = new_pid;
		old = new;
	}
	return (tmp);
}

void	ft_parse_error(char *str)
{
	write(2, "bash: syntax error near unexpected token `", 43);
	write(2, str, ft_strlen(str));
	write(2, "'\n", 2);
	free (str);
	ft_get_status(0, 258, 1);
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

	ft_get_status(0, 1, 1);
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
