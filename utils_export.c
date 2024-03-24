/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 20:00:06 by abdeltif          #+#    #+#             */
/*   Updated: 2024/03/23 23:54:16 by ael-fagr         ###   ########.fr       */
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
    new_str = NULL;
    if (!str || !tmp)
        return (-1);
    while (arg->envp[i])
    {
        p = ft_split(arg->envp[i], '=');
        if (ft_strcmp(p[0], str) == 0)
        {
            new_str = ft_strjoin(str, "=");
            new_str = ft_strjoin(new_str, tmp);
            printf("new_str = %s\n", new_str);
            arg->envp[i] = ft_strdup(new_str);
            if (!arg->envp[i])
            {
                free(new_str);
                return (-1);
            }
            free(new_str);
            return (1);
        }
        (ft_free(p), p = NULL);
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
    i = 0;
    while (new_env[i])
        printf("new env = %s\n", new_env[i++]);
	ft_free(arg->envp);
    arg->envp = new_env;
    return (arg->envp);
}
