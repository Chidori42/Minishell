/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 00:26:36 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/23 04:06:25 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_list(t_cmd *lst)
{
	int			i;
	t_cmd		*tmp;

	while (lst)
	{
		i = -1;
		tmp = lst;
		while (lst->data && lst->data[++i])
			free (lst->data[i]);
		free (lst->data);
		i = -1;
		while (lst->redir && lst->redir[++i])
			free (lst->redir[i]);
		free (lst->redir);
		i = -1;
		while (lst->ref && lst->ref[++i])
			free (lst->ref[i]);
		free (lst->ref);
		lst = lst->next;
		free (tmp);
	}
}

static void	ft_set_fds(t_pars *as, t_cmd *nd, int i)
{
	if ((i % 2) != 0)
	{
		nd->in = &as->p_2[0];
		nd->out = &as->p_1[1];
	}
	else if ((i % 2) == 0)
	{
		nd->in = &as->p_1[0];
		nd->out = &as->p_2[1];
	}
}

static t_cmd	*ft_create_node()
{
	t_cmd		*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (node)
	{
		node->in = NULL;
		node->out = NULL;
		node->data = NULL;
		node->redir = NULL;
		node->ref = NULL;
		node->next = NULL;
	}	
	return (node);
}

static void ft_lst_add_back(t_cmd **head, t_cmd *new)
{
	t_cmd		*tmp;

	if (head && new)
	{
		if (*head)
		{
			tmp = *head;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
		else
			*head = new;
	}
}

t_cmd	*ft_create_list(t_pars *args, char **tab)
{
	int			i;
	int			j;
	t_cmd		*node;
	t_cmd		*head;

	j = 0;
	i = -1;
	head = NULL;
	while (args && tab && tab[++i])
	{
		node = ft_create_node();
		if (node)
		{
			ft_set_fds(args, node, ++j);
			node->data = ft_get_cmd(args, tab, i);
			node->redir = ft_get_redir(args, tab, i);
			node->ref = ft_get_redir(args, tab, i);
			ft_lst_add_back(&head, node);
		}
		while (tab[i + 1] && tab[++i] && \
			ft_strcmp("|", tab[i]))
			;
	}
	ft_remove_quotes(head);
	return (head);
}
