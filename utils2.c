/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 01:01:12 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/03/23 08:21:52 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    check_env(t_data *arg, char *str)
{
	int i;

	i = 0;
	while (arg->envp[i])
	{
		if (ft_strncmp(arg->envp[i], str, ft_strlen(str)) == 0)
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

int  check_var(char *p)
{
	int i;

	i = 0;
	while (p[i])
	{
		if (p[i] != '_' && !ft_isalnum(p[i]))
			return(perror("unset: =: invalid parameter name"), 1);
		i++;
	}
	return (0);
}

int	ft_unset(t_data *arg, char *p)
{
	char **str;

	str = ft_split(p, ' ');
	if (!str)
		return (free(p), -1);
	if (str[1])
	{
		if (check_var(str[1]) == 1)
			return (1);
		if (ft_strlen(str[1]) > 256)
			return (ft_free(str), ft_putstr_fd("Error\n", 2), 1);
		check_env(arg, str[1]);
	}
	ft_free(str);
	return (0);
}
