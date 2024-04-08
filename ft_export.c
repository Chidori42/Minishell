/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 01:06:22 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/04/07 21:52:50 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_dup_env(char **envp, char *var)
{
	int		i;
	char	**env;
	char	*tmp;

	i = 0;
	while (envp && envp[i])
	{
		tmp = ft_strs_join(tmp, ft_strdup(envp[i]));
		tmp = ft_strs_join(tmp, ft_strdup("\n"));
		if (!tmp)
			return (NULL);
		i++;
	}
	tmp = ft_strs_join(tmp, var);
	if (!tmp)
		return (NULL);
	env = ft_split(tmp, '\n');
	return (free(tmp), env);
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
			envp[i] = ft_strs_join(envp[i], \
			ft_substr(arg, (ft_var_len(arg) + 2), \
			(ft_strlen(arg) - ft_strlen(v_name))));
		}
		else if (!ft_strcmp(opr, "="))
			envp[i] = ft_strdup(arg);
	}
	return (free (tmp), free(v_name), b);
}

static char	**ft_check_set(char **envp, char *v_name, char *str)
{
	int	i;
	int	b;

	i = -1;
	b = 0;
	while (str[++i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			b = 1;
	}
	if (b)
		envp = ft_dup_env(envp, ft_strs_join(ft_strjoin(v_name, "="), \
			ft_substr(str, (ft_var_len(str) + 2), \
			(ft_strlen(str) - ft_strlen(v_name)))));
	else
		envp = ft_dup_env(envp, ft_strs_join(ft_strjoin(v_name, "="), \
			ft_substr(str, (ft_var_len(str) + 1), \
			(ft_strlen(str) - ft_strlen(v_name)))));
	return (envp);
}

static char	**ft_set_variable(char **envp, char *arg)
{
	int			i;
	int			b;
	char		*v_name;
	char		**tmp;

	b = 1;
	i = -1;
	v_name = ft_substr(arg, 0, ft_var_len(arg));
	if (arg && envp)
	{
		while (envp[++i])
			b = ft_update_env(envp, arg, i);
		if (b)
		{
			tmp = envp;
			envp = ft_check_set(envp, v_name, arg);
			ft_free_2_dm(tmp);
			free(v_name);
		}
	}
	return (envp);
}

void	ft_export(t_pars *data, char **envp, char **args)
{
	int		i;
	char	*v_name;

	i = -1;
	if (args[1] == NULL)
	{
		while (envp[++i])
		{
			v_name = ft_substr(envp[i], 0, ft_var_len(envp[i]));
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(v_name, 1);
			write(1, "=\"", 2);
			ft_putstr_fd(ft_substr(envp[i], (ft_var_len(envp[i]) + 2), \
			(ft_strlen(envp[i]) - ft_strlen(v_name))), 1);
			write(1, "\"\n", 2);
		}
	}
	i = 0;
	while (envp && args && args[++i])
	{
		if (!ft_check_arg(args[i]) && \
			!ft_check_var(args[i]))
			data->envp = ft_set_variable(envp, args[i]);
	}
}
