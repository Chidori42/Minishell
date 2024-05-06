/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:00:06 by abdeltif          #+#    #+#             */
/*   Updated: 2024/05/05 11:19:35 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_is_space(char c)
{
	if ((9 < c && c < 13) || (c == 32))
		return (1);
	return (0);
}

int	ft_var_len(char *arg)
{
	int			len;

	len = 0;
	while (arg && arg[len] && (arg[len] != '+') && \
		(arg[len] != '='))
		len++;
	return (len);
}

int	ft_check_arg(char *arg, int *st)
{
	int			i;
	char		*err_des;

	i = -1;
	err_des = "not a valid identifier";
	while (arg && arg[++i])
	{
		if (ft_is_space(arg[i]))
			return (*st = 1, 
				ft_builts_error("export", arg, err_des), 1);
		if (arg[i] == '+' && arg[i + 1] != '=')
			return (*st = 1, 
				ft_builts_error("export", arg, err_des), 1);
		if (arg[i] == '+' || arg[i] == '=')
			break ;
	}
	return (0);
}

int	ft_check_var(char *arg, int *st)
{
	int			i;
	char		*var_name;
	char		*err_des;

	i = 0;
	err_des = "not a valid identifier";
	if (arg)
	{
		var_name = ft_substr(arg, 0, \
			ft_var_len(arg));
		if (var_name && !(ft_isalpha(var_name[i]) || var_name[i] == '_'))
			return (*st = 1, free(var_name), 
					ft_builts_error("export", arg, err_des), 1);
		while (var_name && var_name[++i])
			if (!ft_isalnum(var_name[i]) && \
				var_name[i] != '_')
				return (*st = 1, free(var_name), 
					ft_builts_error("export", arg, err_des), 1);
		free(var_name);
	}
	return (0);
}
