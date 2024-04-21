/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:49:21 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/21 10:15:06 by ael-fagr         ###   ########.fr       */
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

static void	ft_close_fd(t_pars *args, int i)
{
	if (((i % 2) != 0) && (args->p_1[0] != 0) && \
		(close(args->p_1[0]) < 0))
		ft_putendl_fd(strerror(errno), 2);
	else if (((i % 2) == 0) && (args->p_2[0] != 0) && \
		(close(args->p_2[0]) < 0))
		ft_putendl_fd(strerror(errno), 2);
}

char	*ft_getenv(char **envp, char *name)
{
	int			i;
	char		*vl;
	char		**var;

	i = -1;
	while (envp && name && envp[++i])
	{
		var = ft_split(envp[i], '=');
		if (!ft_strcmp(var[0], name))
		{
			vl = ft_strdup(var[1]);
			ft_free_2_dm(var);
			return (vl);
		}
		ft_free_2_dm(var);
	}
	return (NULL);
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

int	ft_execute_cmd(t_pars *args, t_cmd *node, int i)
{
	char		*cmd_path;
	char		*error_msg;

	ft_close_fd(args, i);
	if (!ft_is_there_slash(node->data[0]))
		cmd_path = ft_get_path(args, node->data[0]);
	if ((0 <= dup2(*node->in, 0)) && (0 <= dup2(*node->out, 1)))
	{
		if (execve(cmd_path, node->data, args->envp) < 0)
		{
			error_msg = ft_strjoin("command not found: ", \
				node->data[0]);
			ft_putendl_fd(error_msg, 2);
			free (error_msg);
			exit(127);
		}
	}
	else
		ft_putendl_fd(strerror(errno), 2);
	exit(errno);
}
