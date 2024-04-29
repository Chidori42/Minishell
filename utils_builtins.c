/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 10:06:36 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/04/28 03:19:25 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **p)
{
	int	i;

	i = -1;
	while (p[++i])
		;
	if (i <= 2)
	{
		if (p && p[1])
		{
			while (p[1][++i])
			{
				if (!(p[1][i] >= '0' && p[1][i] <= '9'))
				{
					ft_putendl_fd(" numeric argument required", 2);
					exit(255);
				}
			}
			exit((unsigned char)ft_atoi(p[1]));
		}
		else
			exit(0);
	}
	else
		return (ft_putendl_fd(" too many arguments", 2), 1);
	return (0);
}

int	ft_display_env(t_pars *data)
{
	char	*v_name;
	char	*v_value;
	int		i;

	i = -1;
	while (data->envp && data->envp[++i])
	{
		v_name = ft_substr(data->envp[i], 0, \
			ft_var_len(data->envp[i]));
		if (!v_name)
			return (-1);
		v_value = ft_substr(data->envp[i], \
			(ft_var_len(data->envp[i]) + 1), \
			(ft_strlen(data->envp[i]) - ft_strlen(v_name)));
		if (!ft_strchr(data->envp[i], '='))
			printf("declare -x %s\n", v_name);
		else
			printf("declare -x %s=\"%s\"\n", v_name, v_value);
		(free(v_name), free(v_value));
	}
	return (0);
}
