/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 00:26:36 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/11 06:14:10 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		lst = lst->next;
		free (tmp);
	}
}

static t_cmd	*ft_create_node(char **t, int i)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (node)
	{
		node->in = 0;
		node->out = 1;
		node->next = NULL;
		ft_get_cmd(&node->data, t, i);
		ft_get_redir(&node->redir, t, i);
		if (!node->data && !node->redir)
			return (free(node), NULL);
	}
	return (node);
}

static void	ft_lst_add_back(t_cmd **head, t_cmd *new)
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

int	ft_create_list(t_pars *args, char **tab)
{
	int			i;
	int			j;
	t_cmd		*node;

	j = 0;
	i = -1;
	args->lst = NULL;
	while (args && tab && tab[++i])
	{
		node = ft_create_node(tab, i);
		if (!node)
			return (ft_free_list(args->lst), 1);
		ft_lst_add_back(&args->lst, node);
		while (tab[i + 1] && tab[++i] && \
			ft_strcmp("|", tab[i]))
			;
	}
	return (1 - (1 * (args->lst != NULL)));
}
