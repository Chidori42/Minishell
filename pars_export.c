/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:00:06 by abdeltif          #+#    #+#             */
/*   Updated: 2024/04/29 15:08:28 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_space(char c)
{
	if ((9 < c && c < 13) || (c == 32))
		return (1);
	return (0);
}

static void	ft_export_error(char *arg)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("' not a valid identifier", 2);
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

	i = -1;
	while (arg && arg[++i])
	{
		if (ft_is_space(arg[i]))
			return (*st = 1, ft_export_error(arg), 1);
		if (arg[i] == '+' && arg[i + 1] != '=')
			return (*st = 1, ft_export_error(arg), 1);
		if (arg[i] == '+' || arg[i] == '=')
			break ;
	}
	return (0);
}

int	ft_check_var(char *arg, int *st)
{
	int			i;
	char		*var_name;

	i = 0;
	if (arg)
	{
		var_name = ft_substr(arg, 0, \
			ft_var_len(arg));
		if (var_name && var_name[0] == '-')
			return (*st = 2, free(var_name), ft_export_error(arg), 2);
		if (var_name)
		{
			if (ft_isalpha(var_name[i]) || var_name[i] == '_')
			{
				while (var_name[++i])
					if (!ft_isalnum(var_name[i]) && \
						var_name[i] != '_')
						return (*st = 1, free(var_name), ft_export_error(arg), 1);
			}
			else
				return (*st = 1, free(var_name), ft_export_error(arg), 1);
		}
		free(var_name);
	}
	return (0);
}
