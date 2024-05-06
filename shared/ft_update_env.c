/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:01:48 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/06 03:32:38 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*ft_new_var(char *var, char *old_vl)
{
	char	*name;
	char	*value;
	char	*opr;

	value = NULL;
	opr = ft_get_operator(var);
	name = ft_substr(var, 0, ft_var_len(var));
	if (opr && name)
	{
		value = ft_substr(var, (ft_strlen(name) + \
			ft_strlen(opr)), ft_strlen(var));
		value = ft_strs_join(old_vl, value);
		free(var);
		var = ft_strs_join(ft_strdup(name), ft_strdup("="));
	}
	free (name);
	return (free(opr), ft_strs_join(var, value));
}

int	ft_update_env(char **envp, char *par, int *b, int i)
{
	char		*tmp;
	char		*opr;
	char		*value;
	char		*name;

	value = NULL;
	name = ft_substr(par, 0, ft_var_len(par));
	tmp = ft_substr(envp[i], 0, ft_var_len(envp[i]));
	if (tmp && name && !ft_strcmp(tmp, name))
	{
		*b = 0;
		opr = ft_get_operator(par);
		if (opr)
		{
			if (!ft_strcmp(opr, "+="))
				value = ft_substr(envp[i], (ft_strlen(name) + 1), \
					ft_strlen(envp[i]));
			free (envp[i]);
			envp[i] = ft_new_var(ft_strdup(par), value);
			free(opr);
		}
	}
	return (free (tmp), free(name), *b);
}
