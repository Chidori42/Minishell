/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_complet.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 22:55:04 by bramzil           #+#    #+#             */
/*   Updated: 2024/03/29 11:05:08 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	ft_check_frst(char *input)
{
	if (input && (input[0] == '|' || \
		input[0] == '&' || input[0] == ')'))
		return (ft_parse_error(ft_substr(input, 0, 1)), -1);
	return (0);
}

char	*ft_is_complet(void)
{
	char	*tmp;
	char	*input;
	char	*prompt;

	input = NULL;
	prompt = "Minishell$ ";
	while (true)
	{
		tmp = readline (prompt);
		if (!tmp)
			exit(0);
		input = ft_strs_join(input, tmp);
		if (!ft_check_frst(input) && \
			(ft_check_parse(input) == 1))
		{
			prompt = "> ";
			continue ;
		}
		break ;
	}
	return (input);
}
