/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:01:48 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/08 19:33:54 by bramzil          ###   ########.fr       */
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
	char	**tmp;
	char	*opr;

	value = NULL;
	tmp = NULL;
	opr = ft_get_operator(var);
	name = ft_substr(var, 0, ft_var_len(var));
	if (opr && name)
	{
		value = ft_substr(var, (ft_strlen(name) + \
			ft_strlen(opr)), ft_strlen(var));
		free(var);
		value = ft_strs_join(old_vl, value);
		var = ft_strs_join(ft_strdup(name), \
			ft_strdup("="));
	}
	(free (name), ft_free_2_dm(tmp));
	return (free(opr), ft_strs_join(var, value));
}

int	ft_update_env(t_pars *args, char *par, int *b, int i)
{
	char		*tmp;
	char		*ref;
	char		*opr;
	char		*value;
	char		*name;

	value = NULL;
	name = ft_substr(par, 0, ft_var_len(par));
	tmp = ft_substr(args->envp[i], 0, ft_var_len(args->envp[i]));
	if (tmp && name && !ft_strcmp(tmp, name))
	{
		*b = 0;
		opr = ft_get_operator(par);
		if (opr)
		{
			if (!ft_strcmp(opr, "+="))
				value = ft_substr(args->envp[i], (ft_strlen(name) + 1), \
					ft_strlen(args->envp[i]));
			ref= args->envp[i];
			args->envp[i] = ft_new_var(ft_strdup(par), value);
			(free(opr), free(ref));
		}
	}
	return (free (tmp), free(name), *b);
}
