/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:01:48 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/08 04:40:46 by ael-fagr         ###   ########.fr       */
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

static char	*ft_rm_backslach(char *str)
{
	int		i;
	char	*tmp;
	char	*new_str;

	i = 0;
	new_str = ft_strdup(str);
	while (new_str && new_str[i])
	{
		if (new_str[i] == '\'')
			i = ft_scape_quotes(new_str, i);
		else if ((new_str[i] == '\\') && (new_str[i + 1] == '$'))
		{
			tmp = new_str;
			new_str = ft_substr(new_str, 0, i);
			new_str = ft_strs_join(new_str, \
				ft_substr(tmp, (i + 1), ft_strlen(tmp) - i));
			free(tmp);
		}
		if (new_str[i])
			i++;
	}
	free(str);
	return (new_str);
}

char	*ft_new_var(t_pars *args, char *var, char *old_vl)
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
		value = ft_rm_backslach(value);
		tmp = ft_split_fr(value, '\0');
		ft_expander(args, tmp);
		free(var);
		value = ft_strs_join(old_vl, ft_strdup(tmp[0]));
		var = ft_strs_join(ft_strdup(name), ft_strdup("="));
	}
	(free (name), ft_free_2_dm(tmp));
	return (free(opr), ft_strs_join(var, value));
}

int	ft_update_env(t_pars *args, char *par, int *b, int i)
{
	char		*tmp;
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
			free (args->envp[i]);
			args->envp[i] = ft_new_var(args, ft_strdup(par), value);
			free(opr);
		}
	}
	return (free (tmp), free(name), *b);
}
