/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:00:06 by abdeltif          #+#    #+#             */
/*   Updated: 2024/04/25 10:50:46 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_space(char c)
{
	if ((9 < c && c < 13) || (c == 32))
		return (1);
	return (0);
}

static void	ft_export_error(t_pars *args, char *str, int i)
{
	args->ext_st = i;
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("' not a valid identifier", 2);
}

int	ft_check_arg(t_pars *args, char *str)
{
	int			i;

	i = -1;
	while (str && str[++i])
	{
		if (ft_is_space(str[i]))
			return (ft_export_error(args, str, 1), 1);
		if (str[i] == '+' && str[i + 1] != '=')
			return (ft_export_error(args, str, 1), 1);
		if (str[i] == '+' || str[i] == '=')
			break ;
	}
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

int	ft_check_var(t_pars *data, char *arg)
{
	int			i;
	char		*var_name;

	i = 0;
	if (arg)
	{
		var_name = ft_substr(arg, 0, ft_var_len(arg));
		if (var_name)
		{
			if (var_name[0] == '-')
				return (free(var_name), ft_export_error(data, arg, 2), 2);
			if (ft_isalpha(var_name[i]) || \
				var_name[i] == '_')
			{
				while (var_name[++i])
					if (!ft_isalnum(var_name[i]) && \
						var_name[i] != '_')
						return (free(var_name), ft_export_error(data, arg, 1), 1);
			}
			else
				return (free(var_name), ft_export_error(data, arg, 1), 1);
		}
		free(var_name);
	}
	return (0);
}
