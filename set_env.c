/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:32:01 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/04/27 01:02:13 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_update_shell_lvl(t_pars *data)
{
	char		*tmp;
	char		**tab;

	if (data->envp)
	{
		tmp = ft_strs_join(ft_strdup("export "), \
			ft_getenv(data->envp, "SHLVL"));
		tab = ft_split(tmp, ' ');
		if (tab && tab[0] && tab[1])
		{
			free(tmp);
			tmp = tab[1];
			tab[1] = ft_itoa(ft_atoi(tab[1]) + 1);
			tab[1] = ft_strs_join(ft_strdup("SHLVL="), tab[1]);
			ft_export(data, tab);
		}
		ft_free_2_dm(tab);
		free(tmp);
	}
}

void	ft_set_env(t_pars *data, char **env)
{
	if (data)
	{
		if (env && !env[0])
		{
			data->def_path = "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.";
			data->envp = (char **)malloc(sizeof(char *) * 5);
			data->envp[0] = ft_strdup("OLDPWD");
			data->envp[1] = ft_strs_join(ft_strdup("PWD="), getcwd(NULL, 0));
			data->envp[2] = ft_strdup("SHLVL=1");
			data->envp[3] = ft_strdup("_=env");
			data->envp[4] = NULL;
		}
		else
		{
			ft_dup_env(env, &data->envp, NULL);
			ft_update_shell_lvl(data);
		}
	}
}
