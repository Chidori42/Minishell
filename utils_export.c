/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeltif <abdeltif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:00:06 by abdeltif          #+#    #+#             */
/*   Updated: 2024/03/23 23:09:55 by abdeltif         ###   ########.fr       */
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

    i = 0;
    new_str = NULL;
    if (!str || !tmp)
        return (-1);
    new_str = ft_strjoin(str, "=");
    new_str = ft_strjoin(new_str, tmp);
    printf("new_str = %s\n", new_str);
    while (arg->envp[i])
    {
        if (ft_strcmp(arg->envp[i], new_str) == 0)
        {
            arg->envp[i] = ft_strdup(new_str);
            if (!arg->envp[i])
            {
                free(new_str);
                return (-1);
            }
            free(new_str);
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
    printf("str = %s\n", str);
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	(ft_free(arg->envp), arg->envp = NULL);
    arg->envp = new_env;
    return (arg->envp);
}
