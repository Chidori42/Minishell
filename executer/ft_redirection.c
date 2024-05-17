/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:49:50 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/13 10:30:59 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_puterror(char *file)
{
	char		*msg;

	msg = ft_strs_join(ft_strdup(file), ft_strdup(": "));
	msg = ft_strs_join(msg, ft_strdup(strerror(errno)));
	ft_putendl_fd(msg, 2);
	free (msg);
	return (-1);
}

static int	ft_open_file(char *pth, char *op)
{
	int			fd;

	fd = -1;
	if (pth && op)
	{
		if (!ft_strcmp(op, "<<"))
		{
			fd = open(pth, O_CREAT | O_RDONLY, 0666);
			unlink (pth);
		}
		else if (!ft_strcmp(op, "<"))
			fd = open(pth, O_RDONLY, 0444);
		else if (!ft_strcmp(op, ">"))
			fd = open(pth, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		else if (!ft_strcmp(op, ">>"))
			fd = open(pth, O_CREAT | O_WRONLY | O_APPEND, 0666);
		if (fd < 0)
			return (ft_puterror(pth), -1);
	}
	return (fd);
}

static int	ft_redir_in(t_cmd *node, char *opr, char *path)
{
	int			fd;

	fd = ft_open_file(path, opr);
	if (fd < 0)
		return (1);
	if ((2 < node->in) && (close(node->in) < 0))
		return (ft_putendl_fd(strerror(errno), 2), \
			close(fd) - 1);
	node->in = fd;
	return (0);
}

static int	ft_redir_out(t_cmd *node, char *opr, char *path)
{
	int		fd;

	fd = ft_open_file(path, opr);
	if (fd < 0)
		return (1);
	if ((2 < node->out) && (close(node->out) < 0))
		return (ft_putendl_fd(strerror(errno), 2), \
			close(fd), -1);
	node->out = fd;
	return (0);
}

int	ft_redirection(t_pars *args, t_cmd *node, int *st)
{
	int			i;

	i = -1;
	(*st) = 0;
	if (node && node->redir)
	{
		(*st) = ft_expand_redir(args, &node->redir);
		while (!(*st) && node->redir[++i])
		{
			if (!ft_strncmp(node->redir[i], ">", 1))
				(*st) = ft_redir_out(node, node->redir[i], \
					node->redir[i + 1]);
			else if (!ft_strncmp(node->redir[i], "<", 1))
				(*st) = ft_redir_in(node, node->redir[i], \
					node->redir[i + 1]);
			i++;
		}
	}
	return (*st);
}
