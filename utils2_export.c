/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 21:31:36 by abdeltif          #+#    #+#             */
/*   Updated: 2024/03/30 14:14:47 by ael-fagr         ###   ########.fr       */
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

void	print_env(t_pars *arg)
{
	int	i;
	char	**tmp;
	char	*var;
	char	*value;

	i = 0;
	tmp = arg->envp;
	while (arg->envp[i])
	{
		var = get_var_name(arg->envp[i], "=");
		value = get_var_name(NULL, "=");
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(var, 1);
		write(1, "=\"", 2);
		ft_putstr_fd(value, 1);
		write(1, "\"\n", 2);
		i++;
	}
	arg->envp = tmp;
}
