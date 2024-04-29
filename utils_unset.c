/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 01:01:12 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/04/29 15:07:01 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_new_env(t_pars *args, char *tmp)
{
	char		**new;
	
	new = ft_split(tmp, '\n');
	if (!new)
		return (free (tmp), -1);
	ft_free_2_dm(args->envp);
	args->envp = new;
	return (free(tmp), 0);
}

static int	check_var(char *p, int *b)
{
	int	i;

	i = 0;
	if (p && p[i] == '-')
		return (*b = 2, ft_putendl_fd("unset: invalid option", 2), 2);
	while (p && p[i])
	{
		if (p[i] != '_' && !ft_isalnum(p[i]))
			return (*b = 1, ft_putendl_fd("not a valid identifier", 2), 1);
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
