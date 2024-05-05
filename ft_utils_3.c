/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 22:56:35 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/05/04 23:03:02 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
