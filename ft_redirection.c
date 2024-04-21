/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:49:50 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/21 13:37:18 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_puterror(char *file)
{
	char		*msg;

	msg = ft_strs_join(ft_strdup(strerror(errno)),
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

static int	ft_redir_in(t_pars *args, t_cmd *node, char **redir)
{
	char		**tmp;

	tmp = (char **)malloc(sizeof(char *) * 2);
	if (!tmp)
		return (-1);
	tmp[0] = ft_strdup(redir[1]);
	tmp[1] = NULL;
	if (*node->out != 1 && (close(*node->in) < 0))
		return (ft_putendl_fd(strerror(errno), 2), -1);
	if (ft_strcmp(redir[0], "<<") && ft_expander(args, tmp) && \
		(1 < ft_count_words(tmp[0])))
		return(ft_free_2_dm(tmp), \
			ft_putendl_fd(ft_strs_join(ft_strdup(redir[1]), \
			ft_strdup(": ambiguous redirect")), 2), -1);
	*node->in = ft_open_file(args, redir[1], redir[2], redir[0]);
	if (*node->in < 0)
	{
		*node->in = 1;
		return (ft_free_2_dm(tmp), -1);
	}
	return (ft_free_2_dm(tmp), 0);
}

static int	ft_redir_out(t_pars *args, t_cmd *node, char **redir)
{
	char		**tmp;

	tmp = (char **)malloc(sizeof(char *) * 2);
	if (!tmp)
		return (-1);
	tmp[0] = ft_strdup(redir[1]);
	tmp[1] = NULL;
	if (*node->out != 1 && (close(*node->out) < 0))
		return (ft_putendl_fd(strerror(errno), 2), -1);
	if (ft_expander(args, tmp) && (1 < ft_count_words(tmp[0])))
		return(ft_free_2_dm(tmp), \
			ft_putendl_fd(ft_strs_join(ft_strdup(redir[1]), \
			ft_strdup(": ambiguous redirect")), 2), -1);
	*node->out = ft_open_file(args, redir[1], NULL, redir[0]);
	if (*node->out < 0)
	{
		*node->out = 1;
		return (ft_free_2_dm(tmp), -1);
	}
	return (ft_free_2_dm(tmp), 0);
}

int	ft_redirection(t_pars *args, t_cmd *node)
{
	int			i;
	char		**redir;

	i = -1;
	redir = NULL;
	if (node && node->redir)
	{
		while (node->redir[++i])
		{
			redir = (char **)malloc(sizeof(char*) * 3);
			if (!redir)
				return (-1);
			redir[0] = node->redir[i];
			redir[1] = node->redir[i + 1];
			redir[2] = node->ref[i];
			if (!ft_strncmp(node->redir[i], ">", 1) && \
				(ft_redir_out(args, node, redir) < 0))
				return (free(redir), -1);
			else if (!ft_strncmp(node->redir[i], "<", 1) && \
				(ft_redir_in(args, node, redir) < 0))
				return (free(redir), -1);
		}
	}
	return (free(redir), 0);
}
