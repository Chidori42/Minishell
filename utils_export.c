/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeltif <abdeltif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:00:06 by abdeltif          #+#    #+#             */
/*   Updated: 2024/03/24 21:42:56 by abdeltif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int isvalid_var_name(char *str)
{
    int i;

    i = 1;
    if (!ft_isalpha(str[0]) && str[0] != '_')
        return 0;
    while (str[i] != '\0')
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return 0;
        i++;
    }
    return (1);
}

int	check_repeat_var(t_data *arg, char *str, char *tmp)
{
    int		i;
    char    *new_str;
    char    **p;

    i = 0;
    new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(tmp) + 2));
    if (!str || !tmp)
        return (-1);
    while (arg->envp[i])
    {
        p = ft_split(arg->envp[i], '=');
        if (ft_strcmp(p[0], str) == 0)
        {
            ft_strcpy(new_str, str);
            strcat(new_str, "=");
            strcat(new_str, tmp);
            (free(arg->envp[i]) , arg->envp[i] = NULL);
            arg->envp[i] = ft_strdup(new_str);
            if (!arg->envp[i])
            {
                free(new_str);
                return (-1);
            }
            return (1);
        }
        i++;
    }
    return (0);
}

char **set_new_env(t_data *arg, char *str)
{
    int	i;

	i = 0;
	while (arg->envp[i])
		i++;
	char **new_env = (char **)malloc((i + 2) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (arg->envp[i])
	{
		new_env[i] = ft_strdup(arg->envp[i]);
        if (!new_env[i])
            return (NULL);
		i++;
	}
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	ft_free(arg->envp);
    arg->envp = new_env;
    return (arg->envp);
}

char	*get_variable(char *str, char	*op)
{
    int         i;

    i = 0;
	while (str[i] != '\0')
	{
		if (ft_strchr(op, str[i]) != NULL)
			break;    
		i++;
	}
    char *tmp = strndup(str, i);
	return (tmp);
}

int ft_check_vars(char **str)
{
    int     i;
    int     j;
    char    *name;

    i = 0;
    j = 0;
    while (str[i])
	{
		name = get_variable(str[i], "=");
		if (isvalid_var_name(name) != 1)
            j = 1;
		i++;
	}
    return (j);
}
