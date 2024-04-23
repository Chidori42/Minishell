/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 10:06:36 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/04/23 03:11:50 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_check_set(char **envp, char *v_name, char *str)
{
	int		t[2];
	char	*value;
	char	**tmp;
	char	*tmp2;
	char	*new_var;

	t[1] = 0;
	t[0] = -1;
	new_var = NULL;
	while (str && str[++t[0]])
		if ((str[t[0]] == '+') && (str[t[0] + 1] == '=') && ++t[1])
			break ;
	if (str && ft_strchr(str, '='))
		new_var = ft_strs_join(ft_strdup(v_name), ft_strdup("="));
	else
		new_var = ft_strdup(v_name);
	if (str && t[1] == 1)
		value = ft_substr(str, (ft_var_len(str) + 2), \
			(ft_strlen(str) - ft_strlen(v_name)));
	else
		value = ft_substr(str, (ft_var_len(str) + 1), \
			(ft_strlen(str) - ft_strlen(v_name)));
	tmp2 = ft_strs_join(new_var, value);
	tmp = ft_dup_env(envp, tmp2);
	return (ft_free_2_dm(envp), free(tmp2), tmp);
}

void ft_display_env(t_pars *data)
{
	char	*v_name;
	char	*v_value;
	int		i;

	i = -1;
	while (data->envp && data->envp[++i])
	{
		v_name = ft_substr(data->envp[i], 0, ft_var_len(data->envp[i]));
		v_value = ft_substr(data->envp[i], \
		(ft_var_len(data->envp[i]) + 1), \
		(ft_strlen(data->envp[i]) - ft_strlen(v_name)));
		if (!ft_strchr(data->envp[i], '='))
			printf("declare -x %s\n", v_name);
		else if (ft_strcmp(data->envp[i], "_=/usr/bin/env"))
		{
			if (v_value && !v_value[0])
				printf("declare -x %s=\'\'\n", v_name);
			else
				printf("declare -x %s=\"%s\"\n", v_name, v_value);
		}
		(free(v_name), free(v_value));
	}
}
