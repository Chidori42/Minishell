/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 01:06:22 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/04/27 06:01:21 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_dup_env(char **envp, char ***new, char *var)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	tmp = ft_strdup("");
	if (!tmp)
		return (-1);
	while (envp && envp[i])
	{
		tmp = ft_strs_join(tmp, \
			ft_strs_join(ft_strdup(envp[i]), \
			ft_strdup("\n")));
		if (!tmp)
			return (-1);
		i++;
	}
	str = ft_strs_join(tmp, ft_strdup(var));
	if (!str)
		return (-1);
	*new = ft_split(str, '\n');
	if (!new)
		return (free (str), -1);
	return (free(str), 0);
}

static int	ft_set_variable(t_pars *args, char *par)
{
	int			i;
	int			b;
	char		**new;
	char		*opr;

	b = 1;
	i = -1;
	opr = NULL;
	while (par && args->envp && args->envp[++i])
		if (!ft_update_env(args->envp, par, &b, i))
			break ;
	if (b && par && args->envp)
	{
		opr = ft_get_operator(par);
		if (!ft_strcmp(opr, "+="))
			par = ft_strs_join(ft_substr(par, 0, ft_var_len(par)), \
				ft_substr(par, ft_var_len(par) + 1, ft_strlen(par)));
		else
			par = ft_strdup(par);
		if (!par)
			return (-1);
		if (!ft_dup_env(args->envp, &new, par))
			(free(par), ft_free_2_dm(args->envp), args->envp = new);
	}
	return (free(opr), 0);
}

int	ft_export(t_pars *args, char **pars)
{
	int		i;
	int		st;

	i = 0;
	st = 0;
	if (args && pars && !pars[1])
		ft_display_env(args);
	else if (args)
	{
		while (args->envp && pars && pars[++i])
		{
			if (!ft_check_var(pars[i], &st) && \
				!ft_check_arg(pars[i], &st))
				st = ft_set_variable(args, pars[i]);
		}
	}
	return (st);
}
