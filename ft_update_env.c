/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:01:48 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/27 05:20:44 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_operator(char *arg)
{
	int			i;

	if (arg)
	{
		i = ft_var_len(arg);
		if (arg && arg[i] == '+')
			return (ft_substr(arg, i, 2));
		else if (arg && arg[i] == '=')
			return (ft_substr(arg, i, 1));
	}
	return (NULL);
}

static int	ft_appnd(char **envp, char *arg, char *name, int i)
{
	char		*tmp;

	tmp = ft_strs_join(ft_strdup(envp[i]), \
		ft_substr(arg, (ft_var_len(arg) + 2), \
		(ft_strlen(arg) - ft_strlen(name))));
	if (!tmp)
		return (1);
	free (envp[i]);
	envp[i] = tmp;
	return (0);
}

int	ft_update_env(char **envp, char *par, int *b, int i)
{
	char		*opr;
	char		*tmp;
	char		*tmp_1;
	char		*name;

	*b = 1;
	if (!envp || !par)
		return (-1);
	name = ft_substr(par, 0, ft_var_len(par));
	tmp = ft_substr(envp[i], 0, ft_var_len(envp[i]));
	opr = ft_get_operator(par);
	if (tmp && name && !ft_strcmp(tmp, name))
	{
		*b = 0;
		tmp_1 = ft_strdup(par);
		if (!tmp_1)
			return (free(opr), free (tmp), free(name), *b);
		if (opr && !ft_strcmp(opr, "+="))
			(free(tmp_1), ft_appnd(envp, par, name, i));
		else if (opr && !ft_strcmp(opr, "="))
			(free (envp[i]), envp[i] = tmp_1);
		else if (opr)
			(free (envp[i]), envp[i] = tmp_1);
	}
	return (free(opr), free (tmp), free(name), *b);
}
