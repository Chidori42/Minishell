/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:49:21 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/25 00:57:01 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_there_slash(char *s)
{
	int			i;

	i = -1;
	while (s && s[++i])
		if (s[i] == '/')
			return (1);
	return (0);
}

static char	*ft_get_path(t_pars *args, char *cmd)
{
	int			i;
	char		*tmp;
	char		**paths;
	char		*cmd_path;

	i = -1;
	cmd_path = cmd;
	tmp = ft_getenv(args->envp, "PATH");
	if (!tmp)
		tmp = ft_strdup(args->def_path);
	paths = ft_split(tmp, ':');
	if (paths)
	{
		while (paths[++i])
		{
			paths[i] = ft_strs_join(paths[i], ft_strdup("/"));
			cmd_path = ft_strs_join(ft_strdup(paths[i]), \
				ft_strdup(cmd));
			if (0 <= access(cmd_path, 01111))
				return (ft_free_2_dm(paths), free(tmp), cmd_path);
			free (cmd_path);
			cmd_path = NULL;
		}
	}
	return (ft_free_2_dm(paths), free(tmp), cmd);
}

int	ft_execute_cmd(t_pars *args, t_cmd *node)
{
	char		*cmd_path;
	char		*error_msg;

	args->ext_st = 0;
	if (args && node)
	{
		cmd_path = node->data[0];
		if (ft_dup_fd(node->in, 0) || ft_dup_fd(node->out, 1))
			return (errno);
		if (!ft_is_there_slash(node->data[0]))
			cmd_path = ft_get_path(args, node->data[0]);
		if (ft_is_builtin(node->data))
			args->ext_st = ft_builtins(node, args, 1);
		else if (execve(cmd_path, node->data, args->envp) < 0)
		{
			free (cmd_path);
			error_msg = ft_strjoin("command not found: ", \
				node->data[0]);
			ft_putendl_fd(error_msg, 2);
			return (free (error_msg), 127);
		};
		free (cmd_path);
	}
	return (args->ext_st);
}
