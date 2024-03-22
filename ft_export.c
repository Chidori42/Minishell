/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:34:14 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/03/21 20:11:46 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_repeat_var(t_data *arg, char *str, char *tmp)
{
	int		i;

	i = 0;
	if (!str || !tmp)
		return (free(str), free(tmp), -1);
	while (arg->envp[i])
	{
		if (ft_strncmp(arg->envp[i], str, ft_strlen(str)) == 0)
		{
			str = ft_strjoin(str, "=");
			str = ft_strjoin(str, tmp);
			arg->envp[i] = ft_strdup(str);
			if (!arg->envp[i])
				return (free(arg->envp[i]), -1);
			free(tmp);
			return (1);
		}
		i++;
	}
	free(str);
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
	set_new_env(arg, new_var);
    return (0);
}

char	*get_var_name(char *str, char	*op)
{
	char		*token_start;
    static char	*next_token = NULL;

    if (str != NULL)
        next_token = str;
    if (next_token == NULL)
        return (free(str), NULL);
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

int	ft_export(t_data *arg, char *p)
{
    char	**str;
    char	*name;
    char	*value;
    int		i;

    str = ft_split(p, ' ');
    if (!str)
        return (ft_free(str), -1);

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
	{
        i = 1;
        while (str[i])
		{
            if (str[i][0] == '=')
                return (printf("Error\n"), ft_free(str), -1);
            name = get_var_name(str[i], "=");
            if (!name)
                return (-1);
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
    }
	ft_free(str);
    return 0;
}
