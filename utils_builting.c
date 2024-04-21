/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 10:06:36 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/04/21 10:48:08 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_check_set(char **envp, char *v_name, char *str)
{
	int		i;
	char	*value;
	char	**tmp;
	char	*tmp2;
	char	*new_var;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
		{
			i = 1;
			break ;
		}
	}
	new_var = ft_strs_join(ft_strdup(v_name), ft_strdup("="));
	if (i == 1)
		value = ft_substr(str, (ft_var_len(str) + 2), \
			(ft_strlen(str) - ft_strlen(v_name)));
	else
		value = ft_substr(str, (ft_var_len(str) + 1), \
			(ft_strlen(str) - ft_strlen(v_name)));
	tmp2 = ft_strs_join(new_var, value);
	tmp = ft_dup_env(envp, tmp2);
	return (ft_free_2_dm(envp), free(tmp2), tmp);
}
