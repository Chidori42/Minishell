/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 00:26:36 by bramzil           #+#    #+#             */
/*   Updated: 2024/03/27 01:40:32 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_list(t_cmd *lst)
{
	int			i;
	t_cmd		*tmp;

	i = -1;
	while (lst)
	{
		tmp = lst;
		while (lst->data[++i])
			free (lst->data[i]);
		free (lst->redir);
		lst = lst->next;
		free (tmp);
	}
}

static t_cmd	*ft_create_node()
{
	t_cmd		*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (node)
	{
		node->in = 0;
		node->out = 1;
		node->data = NULL;
		node->redir = NULL;
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

t_cmd	*ft_create_list(char **tab)
{
	int			i;
	t_cmd		*node;
	t_cmd		*head;

	i = -1;
	head = NULL;
	while (tab && tab[++i])
	{
		node = ft_create_node();
		if (node)
		{
			node->data = ft_get_cmd(tab, i);
			node->redir = ft_get_redir(tab, i);
			ft_lst_add_back(&head, node);
		}
		while (tab[i + 1] && tab[++i] && \
			ft_strcmp("|", tab[i]))
			;
	}
	return (head);
}