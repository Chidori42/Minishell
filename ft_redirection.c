/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:49:50 by bramzil           #+#    #+#             */
/*   Updated: 2024/03/30 07:10:30 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_open_file(char *path, char *opr)
{
	int			fd;

	fd = -1;
	if (path && opr)
	{
		if (!ft_strcmp(opr, "<") && \
			(fd = open(path, O_RDONLY, 0444)) < 0)
			return (perror("Error"), -1);
		else if (!ft_strcmp(opr, ">") && \
			(fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666)) < 0)
			return (perror("Error"), -1);
		else if (!ft_strcmp(opr, ">>") && \
			(fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666)) < 0)
			return (perror("Error"), -1);
	}
	return (fd);
}

static int	ft_redir_in(t_cmd *node, char *opr, char *file)
{
	if (*node->in != 0 && (close (*node->in) < 0))
		return (perror("Error"), -1);
	*node->in = ft_open_file(file, opr);
	if (*node->in < 0)
	{
		*node->in = 0;
		return (-1);
	}
	return (0);
}

static int	ft_redir_out(t_cmd *node, char *opr, char *file)
{
	printf("from stdout: %d\n", *node->out);
	if (*node->out != 1 && (close(*node->out) < 0))
		return (perror("Error"), -1);
	*node->out = ft_open_file(file, opr);
	if (*node->out < 0)
	{
		*node->out = 1;
		return (-1);
	}
	printf("from stdout: %d\n", *node->out);
	return (0);
}

int	ft_redirection(t_cmd *node)
{
	int			i;
	char		**tab;

	i = -1;
	if (node && node->redir)
	{
		tab = ft_split(node->redir, ' ');
		while (tab && tab[++i])
		{
			if (!ft_strncmp(tab[i], ">", 1) && \
				(ft_redir_out(node, tab[i], tab[i + 1]) < 0))
				return (-1);
			else if (!ft_strncmp(tab[i], "<", 2) && \
				(ft_redir_in(node, tab[i], tab[i + 1]) < 0))
				return (-1);
				
		}
		ft_free_2_dm(tab);
	}
	return (0);
}
