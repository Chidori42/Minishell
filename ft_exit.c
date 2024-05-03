/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:59:54 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/05/03 16:13:28 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_cmd *node)
{
	int	i;

	i = -1;
	if (node->data && node->data[1])
	{
		if (node->data[1][0] == '-' || node->data[1][0] == '+')
			++i;
		while (node->data[1][++i])
			if (!ft_isdigit(node->data[1][i]))
				return (ft_builts_error("exit", node->data[1], \
					"numeric argument required"), exit(255), 0);
		if (node->data[2])
			return (ft_builts_error("exit", node->data[2], \
				"too many arguments"), 1);
		exit((unsigned char)ft_atoi(node->data[1]));
	}
	return (exit(0), 0);
}
