/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 10:06:36 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/05/06 00:35:54 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_builts_error(char *cmd, char *err, char *des)
{
	ft_putstr_fd("mini: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd("': ", 2);
	ft_putendl_fd(des, 2);
}

char *ft_getcwd(t_pars *args)
{
	char			*tmp;
	
	tmp = getcwd(NULL, 0);
	if (tmp)
	{
		free (args->cwd);
		args->cwd = ft_strdup(tmp);
	}
	return (tmp);
}

void	ft_display_env(t_pars *data, t_cmd *node)
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
			break;
		v_value = ft_substr(data->envp[i], \
			(ft_var_len(data->envp[i]) + 1), \
			(ft_strlen(data->envp[i]) - ft_strlen(v_name)));
		ft_putstr_fd("declare -x ", node->out);
		ft_putstr_fd(v_name, node->out);
		if (v_value && ft_strchr(data->envp[i], '='))
		{
			ft_putstr_fd("=\"", node->out);
			ft_putstr_fd(v_value, node->out);
			ft_putstr_fd("\"", node->out);
		}
		write(node->out, "\n", 1);
		(free(v_name), free(v_value));
	}
}
