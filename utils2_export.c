/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 21:31:36 by abdeltif          #+#    #+#             */
/*   Updated: 2024/03/29 10:30:37 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_change(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	set_to_env(t_pars *arg, char *str, int i)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * ft_strlen(str));
	if (!tmp)
		return (-1);
	ft_strlcpy(tmp, str, i + 1);
	ft_strcat(tmp, "=");
	ft_strcat(tmp, &str[i + 2]);
	set_new_env(arg, tmp);
	free(tmp);
	return (0);
}

int	append_value(t_pars *arg, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
		{
			j = 0;
			while (arg->envp[j])
			{
				if (ft_strncmp(arg->envp[j], str, i - 1) == 0)
				{
					arg->envp[j] = ft_strjoin(arg->envp[j], &str[i + 2]);
					return (1);
				}
				j++;
			}
			set_to_env(arg, str, i);
			return (1);
		}
		i++;
	}
	return (0);
}
