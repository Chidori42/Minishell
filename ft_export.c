/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 01:06:22 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/04/21 10:06:22 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_dup_env(char **envp, char *var)
{
	int		i;
	char	**env;
	char	*str;
	char	*tmp;

	i = 0;
	tmp = ft_strdup("");
	while (envp && envp[i])
	{
		tmp = ft_strs_join(tmp, ft_strs_join(ft_strdup(envp[i]), \
			ft_strdup("\n")));
		if (!tmp)
			return (NULL);
		i++;
	}
	str = ft_strs_join(tmp, ft_strdup(var));
	if (!str)
		return (NULL);
	env = ft_split(str, '\n');
	return (free(str), env);
}

static char	*ft_get_operator(char *arg)
{
	int			i;

	i = ft_var_len(arg);
	if (arg && arg[i] == '+')
		return (ft_substr(arg, i, 2));
	else if (arg && arg[i] == '=')
		return (ft_substr(arg, i, 1));
	return (NULL);
}

static int	ft_update_env(char **envp, char *arg, int i)
{
	int			b;
	char		*opr;
	char		*tmp;
	char		*v_name;

	b = 1;
	opr = ft_get_operator(arg);
	tmp = ft_substr(envp[i], 0, ft_var_len(envp[i]));
	v_name = ft_substr(arg, 0, ft_var_len(arg));
	if (!ft_strcmp(tmp, v_name))
	{
		b = 0;
		if (!ft_strcmp(opr, "+="))
		{
			free(envp[i]);
			envp[i] = ft_strs_join(ft_strdup(envp[i]), \
			ft_substr(arg, (ft_var_len(arg) + 2), \
			(ft_strlen(arg) - ft_strlen(v_name))));
		}
		else if (!ft_strcmp(opr, "="))
			(free(envp[i]), envp[i] = ft_strdup(arg));
	}
	return (free(opr), free (tmp), free(v_name), b);
}

static char	**ft_set_variable(char **envp, char *arg)
{
	int			i;
	int			b;
	char		**tmp;
	char		*v_name;

	b = 1;
	i = -1;
	tmp = NULL;
	v_name = NULL;
	while (envp[++i])
	{
		b = ft_update_env(envp, arg, i);
		if (b == 0)
			return (envp);
	}
	if (b)
	{
		v_name = ft_substr(arg, 0, ft_var_len(arg));
		tmp = ft_check_set(envp, v_name, arg);
		free(v_name);
	}
	return (tmp);
}

int	ft_export(t_pars *data, char **args)
{
	int		i;
	char	*v_name;
	char	*v_value;

	i = -1;
	if (!args[1])
	{
		while (data->envp[++i])
		{
			v_name = ft_substr(data->envp[i], 0, ft_var_len(data->envp[i]));
			v_value = ft_substr(data->envp[i], (ft_var_len(data->envp[i]) + 1), \
			(ft_strlen(data->envp[i]) - ft_strlen(v_name)));
			printf("declare -x %s=\"%s\"\n", v_name, v_value);
			(free(v_name), free(v_value));
		}
	}
	i = 0;
	while (data->envp && args[++i])
	{
		if (!ft_check_arg(args[i]) && \
			!ft_check_var(args[i]))
			data->envp = ft_set_variable(data->envp, args[i]);
	}
	return (0);
}
