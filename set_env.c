/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:32:01 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/04/22 21:06:07 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_set_env(t_pars *data, char **env)
{
    if (!env[0])
    {
        data->def_path = "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.";
        data->envp = (char **)malloc(sizeof(char *) * 5);
        data->envp[0]= ft_strdup("OLDPWD");
        data->envp[1] = ft_strs_join(ft_strdup("PWD="), getcwd(NULL, 0));
        data->envp[2]= ft_strdup("SHLVL=1");
        data->envp[3] = ft_strdup("_=/usr/bin/env");
        data->envp[4] = NULL;
    }
    else
        data->envp = ft_dup_env(env, NULL);
}
