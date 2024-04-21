/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:49:50 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/21 10:56:30 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_puterror(char *file)
{
	char		*msg;

	msg = ft_strs_join(ft_strdup(strerror(errno)), \
	ft_strdup(": "));
	msg = ft_strs_join(msg, ft_strdup(file));
	ft_putendl_fd(msg, 2);
	free (msg);
	return (0);
}

static int	ft_open_file(t_pars *args, char *path, char *ref, char *opr)
{
	int			fd;

	fd = -1;
	if (path && opr)
	{
		if (!ft_strcmp(opr, "<<") && \
			(ft_heredoc(args, path, ref, &fd) < 0))
			return (-1);
		else if (!ft_strcmp(opr, "<") && \
			(fd = open(path, O_RDONLY, 0444)) < 0)
			return (ft_puterror(path), -1);
		else if (!ft_strcmp(opr, ">") && \
			(fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666)) < 0)
			return (ft_puterror(path), -1);
		else if (!ft_strcmp(opr, ">>") && \
			(fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666)) < 0)
			return (ft_puterror(path), -1);
	}
	return (fd);
}

static int	ft_redir_in(t_pars *ags, t_cmd *nd, char *o, char *f, char *r)
{
	if (*nd->in != 0 && (close (*nd->in) < 0))
		return (ft_putendl_fd(strerror(errno), 2), -1);
	*nd->in = ft_open_file(ags, f, r, o);
	if (*nd->in < 0)
	{
		*nd->in = 0;
		return (-1);
	}
	return (0);
}

static int	ft_redir_out(t_pars *args, t_cmd *node, char *opr, char *file)
{
	if (*node->out != 1 && (close(*node->out) < 0))
		return (ft_putendl_fd(strerror(errno), 2), -1);
	*node->out = ft_open_file(args, file, NULL, opr);
	if (*node->out < 0)
	{
		*node->out = 1;
		return (-1);
	}
	return (0);
}

int	ft_redirection(t_pars *args, t_cmd *node)
{
	int			i;

	i = -1;
	if (node && node->redir)
	{
		while (node->redir[++i])
		{
			if (!ft_strncmp(node->redir[i], ">", 1) && \
				(ft_redir_out(args, node, node->redir[i], \
					node->redir[i + 1]) < 0))
				return (-1);
			else if (!ft_strncmp(node->redir[i], "<", 1) && \
				(ft_redir_in(args, node, node->redir[i], \
					node->redir[i + 1], node->ref[i + 1]) < 0))
				return (-1);
		}
	}
	return (0);
}
