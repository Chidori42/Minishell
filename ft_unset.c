/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 01:01:12 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/05/02 02:17:01 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_new_env(t_pars *args, char *tmp)
{
	char		**new;
	
	new = ft_split_fr(tmp, '\n');
	if (!new)
		return (-1);
	ft_free_2_dm(args->envp);
	args->envp = new;
	return (0);
}

static int	check_var(char *p, int *b)
{
	int			i;
	char		*err_des;

	i = 0;
	err_des = "not a valid identifier";
	if (p && (!p[i] || ft_isdigit(p[i])))
		return (*b = 1,
			ft_builts_error("unset", p, err_des), 1);
	while (p && p[i])
	{
		if (p[i] != '_' && !ft_isalnum(p[i]))
			return (*b = 1,
				ft_builts_error("unset", p, err_des), 1);
		i++;
	}
	return (0);
}

static int	remove_var(t_pars *arg, char *str)
{
	int		i;
	char	*tmp;
	char	**p;

	i = -1;
	tmp = NULL;
	while (str && arg->envp && arg->envp[++i])
	{
		p = ft_split(arg->envp[i], '=');
		if (!p)
			return (-1);
		if (ft_strcmp(p[0], str))
		{
			tmp = ft_strs_join(tmp, ft_strdup("\n"));
			if (!tmp)
				return (ft_free_2_dm(p), -1);
			tmp = ft_strs_join(tmp, ft_strdup(arg->envp[i]));
			if (!tmp)
				return (ft_free_2_dm(p), -1);
		}
		ft_free_2_dm(p);
	}
	return (ft_new_env(arg, tmp));
}

int	ft_unset(t_pars *arg, char **p)
{
	int b;
	int i;

	b = 0;
	i = 0;
	if (p)
	{
		while (p[++i])
			if (!check_var(p[i], &b))
				remove_var(arg, p[i]);
	}
	return (b);
}
