/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 10:06:36 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/05/07 01:15:35 by ael-fagr         ###   ########.fr       */
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

void	ft_cd_error(void)
{
	char	*err_msg;

	err_msg = NULL;
	err_msg = ft_strs_join(err_msg, ft_strdup("cd: error retrieving current "));
	err_msg = ft_strs_join(err_msg, ft_strdup("directory: getcwd: cannot "));
	err_msg = ft_strs_join(err_msg, ft_strdup("access parent directories: "));
	err_msg = ft_strs_join(err_msg, ft_strdup("No such file or director"));
	ft_putendl_fd(err_msg, 2);
	free (err_msg);
}

char	*ft_getcwd(t_pars *args)
{
	char			*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp)
	{
		free (args->cwd);
		args->cwd = tmp;
	}
	return (tmp);
}

static void	display(t_cmd *node, char *envp, char *nm, char *vl)
{
	ft_putstr_fd("declare -x ", node->out);
	ft_putstr_fd(nm, node->out);
	if (vl && ft_strchr(envp, '='))
	{
		ft_putstr_fd("=\"", node->out);
		ft_putstr_fd(vl, node->out);
		ft_putstr_fd("\"", node->out);
	}
	write(node->out, "\n", 1);
}

void	ft_display_env(t_pars *args, t_cmd *node)
{
	char	*v_name;
	char	*v_value;
	int		i;

	i = -1;
	while (args->envp && args->envp[++i])
	{
		v_name = ft_substr(args->envp[i], 0, \
			ft_var_len(args->envp[i]));
		if (!v_name)
			break ;
		v_value = ft_substr(args->envp[i], \
			(ft_var_len(args->envp[i]) + 1), \
			(ft_strlen(args->envp[i]) - ft_strlen(v_name)));
		if (v_name && ft_strcmp(v_name, "_"))
			display(node, args->envp[i], v_name, v_value);
		(free(v_name), free(v_value));
	}
}
