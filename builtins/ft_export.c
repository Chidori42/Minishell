/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 01:06:22 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/05/11 06:11:13 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_dup_env(char **envp, char ***new, char *var)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	tmp = ft_strdup("");
	if (!tmp)
		return (free(var), -1);
	while (envp && envp[i])
	{
		tmp = ft_strs_join(tmp, \
			ft_strs_join(ft_strdup(envp[i]), \
			ft_strdup("\n")));
		if (!tmp)
			return (free(var), -1);
		i++;
	}
	str = ft_strs_join(tmp, ft_strdup(var));
	if (!str)
		return (free(var), -1);
	*new = ft_split(str, '\n');
	if (!new)
		return (free(str), free(var), -1);
	return (free(str), free(var), 0);
}

static int	ft_set_variable(t_pars *args, char *par)
{
	int			i;
	int			b;
	char		**new;

	b = 1;
	i = -1;
	while (par && args->envp && args->envp[++i])
		if (!ft_update_env(args, par, &b, i))
			break ;
	if (b && par && args->envp)
		if (!ft_dup_env(args->envp, &new, \
			ft_new_var(ft_strdup(par), NULL)))
			(ft_free_2_dm(args->envp), args->envp = new);
	return (0);
}

int	ft_export(t_pars *args, t_cmd *node, char **pars)
{
	int		i;
	int		st;

	i = 0;
	st = 0;
	if (args && pars && !pars[1])
		ft_display_env(args, node);
	else if (args)
	{
		while (args->envp && pars && pars[++i])
		{
			if (!ft_check_var(pars[i], &st) && \
				!ft_check_arg(pars[i], &st))
				ft_set_variable(args, pars[i]);
		}
	}
	return (st);
}
