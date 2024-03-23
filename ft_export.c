/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeltif <abdeltif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:34:14 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/03/23 20:34:19 by abdeltif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_getenv(t_data *arg, char *name)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (arg->envp[i])
	{
		if (ft_strncmp(arg->envp[i], name, len) == 0)
			return (&(arg->envp[i][len]));
		i++;
	}
	return (NULL);
}

int	my_setenv(t_data *arg, char *name, char *value)
{
	if (my_getenv(arg, name) != NULL)
		return (0);
	int name_len = ft_strlen(name);
	int value_len = ft_strlen(value);
	char *new_var = malloc(name_len + value_len + 2);
	if (!new_var)
		return (-1);
	ft_strcpy(new_var, name);
	strcat(new_var, "=");
	strcat(new_var, value);
	if(set_new_env(arg, new_var) == NULL)
		return (-1);
	free(new_var);
	return (0);
}

char	*get_var_name(char *str, char	*op)
{
	char		*token_start;
	static char	*next_token = NULL;

	if (str != NULL)
		next_token = str;
	if (next_token == NULL)
		return (NULL);
	token_start = next_token;
	while (*next_token != '\0')
	{
		if (ft_strchr(op, *next_token) != NULL)
		{
			*next_token = '\0';
			next_token++;
			break;
		}
		next_token++;
	}
	if (token_start == next_token)
		return (NULL);
	return (token_start);
}

int    ft_set_export(t_data *arg, char **str)
{
	char	*name;
	char	*value;
	int		i;
	
	i = 1;
	while (str[i])
	{
		name = get_var_name(str[i], "=");
		if (isvalid_var_name(name) != 1)
			return (printf("Check var name\n"), -1);
		value = get_var_name(NULL, "=");
		if (!value)
		{
			value = malloc(1);
			if (!value)
				return (-1);
			value[0] = '\0';
		}
		if (check_repeat_var(arg, name, value) != 1)
		{
			if (name && value)
				my_setenv(arg, name, value);
		}
		i++;
	}
	return (0);
}

int	ft_export(t_data *arg, char *p)
{
	char	**str;
	int		i;

	str = ft_split(p, ' ');
	if (!str)
		return (-1);

	if (str[1] == NULL)
	{
		i = 0;
		while (arg->envp[i])
		{
			printf("%s\n", arg->envp[i]);
			i++;
		}
	}
	else
		ft_set_export(arg, str);
	return 0;
}
