/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:49:21 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/06 03:22:44 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_is_there_slash(char *s)
{
	int			i;

	i = -1;
	while (s && s[++i])
		if (s[i] == '/')
			return (1);
	return (0);
}

static int	ft_execut_error(char *cmd)
{
	int			ref;
	DIR			*ptr;

	ref = errno;
	ft_putstr_fd("mini: ", 2);
	ft_putstr_fd(cmd, 2);
	if (ref == 2)
	{
		ft_putendl_fd(": command not found", 2);
		return (127);
	}
	else if (ref == 13)
	{
		ptr = opendir(cmd);
		if (ptr && !closedir(ptr))
			ft_putendl_fd(": is directory", 2);
		else
		{
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(ref), 2);
		}
		return (126);
	}
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
		tmp = ft_strdup(args->path);
	paths = ft_split_fr(tmp, ':');
	if (paths)
	{
		while (paths[++i])
		{
			paths[i] = ft_strs_join(paths[i], ft_strdup("/"));
			cmd_path = ft_strs_join(ft_strdup(paths[i]), \
				ft_strdup(cmd));
			if (0 <= access(cmd_path, 01111))
				return (ft_free_2_dm(paths), cmd_path);
			free (cmd_path);
			cmd_path = NULL;
		}
	}
	return (ft_free_2_dm(paths), cmd);
}

int	ft_execute_cmd(t_pars *args, t_cmd *node)
{
	char		*cmd_path;

	args->ext_st = 0;
	signal(SIGQUIT, ft_child_handler);
	if (args && node)
	{
		cmd_path = node->data[0];
		if (ft_dup_fd(node->in, 0) || ft_dup_fd(node->out, 1))
			return (errno);
		if (!ft_is_there_slash(node->data[0]) && \
			ft_strcmp(node->data[0], ".") && \
			ft_strcmp(node->data[0], ".."))
			cmd_path = ft_get_path(args, node->data[0]);
		if (ft_is_builtin(node->data))
			args->ext_st = ft_builtins(args, node);
		else if ((execve(cmd_path, node->data, args->envp) < 0))
			return (ft_execut_error(cmd_path));
		free (cmd_path);
	}
	return (args->ext_st);
}
