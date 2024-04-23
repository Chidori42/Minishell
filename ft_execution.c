/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:54:26 by bramzil           #+#    #+#             */
/*   Updated: 2024/04/23 04:32:13 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_execute(t_cmd *cmds, t_pars *args)
{
	int			exit;
	char		*buits;

	exit = -1;
	buits = "export echo cd unset pwd env exit";
	while (cmds && args)
	{
		if (ft_strnstr(buits, cmds->data[0], ft_strlen(buits)))
			args->ext_st = ft_builthing(cmds, args);
		else
			args->ext_st = ft_execute_lst(args);
		cmds = cmds->next;
		exit = args->ext_st;
	}
	return (exit);
}

int	ft_execution(t_pars *args)
{
	args->lst = ft_create_list(args, args->tab);
	args->ext_st = ft_check_execute(args->lst, args);
	ft_free_list(args->lst);
	ft_free_2_dm(args->tab);
	args->input = NULL;
	return (0);
}