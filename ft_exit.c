/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:59:54 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/05/04 18:21:57 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strcmp_nb(char *str)
{
	char		*ref;
	char		*tmp;

	tmp = str;
	ref = "9223372036854775807";
	if (!str)
		return (1);
	if (str && (str[0] == '-'))
	{
		tmp = &str[1];
		ref = "9223372036854775808";
	}
	if (ft_strlen(tmp) == ft_strlen(ref))
		return (ft_strcmp(ref, tmp));
	return (ft_strlen(ref) - ft_strlen(tmp));
}

int	ft_exit(t_cmd *node)
{
	int	i;

	i = -1;
	if (node->data && node->data[1])
	{
		if (node->data[1][0] == '-' || node->data[1][0] == '+')
			++i;
		while (node->data[1][++i])
			if (!ft_isdigit(node->data[1][i]) || \
				(ft_strcmp_nb(node->data[1]) < 0))
				return (ft_builts_error("exit", node->data[1], \
					"numeric argument required"), exit(255), 0);
		if (node->data[2])
			return (ft_builts_error("exit", node->data[2], \
				"too many arguments"), 1);
		exit((unsigned char)ft_atoi(node->data[1]));
	}
	return (exit(0), 0);
}
