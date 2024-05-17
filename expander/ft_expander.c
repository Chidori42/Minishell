/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:06:10 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/13 20:53:05 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_expand_redir(t_pars *args, char ***redir)
{
	int			i;
	char		*ref;
	char		*tmp;

	i = -1;
	ref = NULL;
	tmp = NULL;
	while ((*redir) && (*redir)[++i])
	{
		tmp = ft_strdup((*redir)[i]);
		ref = ft_expand_it(tmp, 1);
		tmp = ft_expand(args, tmp, ref, 0);
		if (tmp)
		{
			if ((1 != ft_count_words(tmp)))
				return (free(tmp), \
					ft_redir_error((*redir)[i]));
			(free((*redir)[i]), (*redir)[i] = tmp);
		}
		else
			return (-1);
	}
	return (0);
}

int	ft_expand_cmd(t_pars *args, char ***tab, int fl)
{
	int			i;
	int			en;
	char		*ref;
	char		*new;

	i = -1;
	while ((*tab) && (*tab)[++i])
	{
		ref = ft_expand_it((*tab)[i], fl);
		en = ft_encapsule_or((*tab)[0], (*tab)[i], ref);
		ref = ft_expand(args, ft_strdup((*tab)[i]), ref, en);
		new = ft_add_scaper(ref);
		if (new)
			(free((*tab)[i]), ((*tab)[i] = new));
		else
			return (-1);
	}
	return (0);
}

int	ft_expander(t_pars *args, t_cmd *lst)
{
	t_cmd		*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_expand_cmd(args, &tmp->data, 1) || \
			ft_resplit_tok(&tmp->data) || \
			ft_remove_quotes(tmp) || \
			ft_remove_scaper(&tmp->data))
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
