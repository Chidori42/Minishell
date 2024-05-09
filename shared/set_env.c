/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:32:01 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/05/09 03:25:15 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_isdigit_only(char *str)
{
	int			i;

	i = -1;
	while (str && str[++i])
		if (!ft_isdigit(str[i]))
			return (1);
	return (0);
}

static void	ft_update_shell_lvl(t_pars *data, t_cmd *node)
{
	char		*tmp;
	char		**tab;

	if (data->envp)
	{
		tmp = ft_strs_join(ft_strdup("export "), \
			ft_getenv(data->envp, ft_strdup("SHLVL")));
		tab = ft_split_fr(tmp, ' ');
		if (tab && tab[0] && tab[1])
		{
			tmp = tab[1];
			if (ft_isdigit_only(tab[1]))
				tab[1] = ft_strdup("1");
			else
				tab[1] = ft_itoa(ft_atoi(tab[1]) + 1);
			tab[1] = ft_strs_join(ft_strdup("SHLVL="), tab[1]);
			ft_export(data, node, tab);
			free(tmp);
		}
		ft_free_2_dm(tab);
	}
}

void	ft_set_env(t_pars *args, char **env)
{
	char		**tmp;

	tmp = NULL;
	args->cwd = NULL;
	tcgetattr(fileno(stdout), &args->term_st);
	if (args && env && !env[0])
	{
		args->envp = ft_split_fr(ft_strdup("OLDPWD PWD SHLVL=1 _"), ' ');
		if (args->envp)
			tmp = ft_split_fr((ft_strs_join(ft_strdup("export "), \
				ft_strs_join(ft_strdup("PWD="), \
					ft_strdup(ft_getcwd(args))))), ' ');
		if (tmp)
			ft_export(args, NULL, tmp);
	}
	else if (args)
	{
		ft_dup_env(env, &args->envp, NULL);
		tmp = ft_split_fr(ft_strdup("unset OLDPWD"), ' ');
		if (tmp)
			ft_unset(args, tmp);
		ft_export(args, NULL, tmp);
		ft_update_shell_lvl(args, NULL);
	}
	ft_free_2_dm(tmp);
}
