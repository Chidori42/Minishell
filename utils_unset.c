/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 01:01:12 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/03/29 15:11:11 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_env(t_pars *arg, char *str)
{
	int		i;
	char	**p;

	i = 0;
	while (arg->envp[i])
	{
		p = ft_split(arg->envp[i], '=');
		if (ft_strcmp(p[0], str) == 0)
		{
			while (arg->envp[i + 1])
			{
				arg->envp[i] = ft_strdup(arg->envp[i + 1]);
				if (!arg->envp[i])
					return (free(arg->envp[i]), -1);
				i++;
			}
			arg->envp[i] = NULL;
			break ;
		}
		i++;
	}
	return (0);
}

int	check_var(char *p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		if (p[i] != '_' && !ft_isalnum(p[i]))
			return (perror ("unset: invalid option"), 1);
		i++;
	}
	return (0);
}

int	ft_unset(t_pars *arg, char **p)
{
	if (p[1])
	{
		if (check_var(p[1]) == 1)
			return (1);
		if (ft_strlen(p[1]) > 256)
			return (ft_free(p), ft_putstr_fd("Error\n", 2), 1);
		check_env(arg, p[1]);
	}
	ft_free(p);
	return (0);
}
