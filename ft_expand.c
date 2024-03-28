/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeltif <abdeltif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 00:09:18 by abdeltif          #+#    #+#             */
/*   Updated: 2024/03/27 03:08:19 by abdeltif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_check_env(t_data *arg, char *name)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (arg->envp[i])
	{
		if (ft_strncmp(arg->envp[i], name, len) == 0)
			return (&(arg->envp[i][len + 1]));
		i++;
	}
	return (NULL);
}

void    ft_expand(t_data *arg, char **str)
{
    int i;
    int j;
    char *tmp = NULL;
    char *tmp2 = NULL;
    
    i = 0;
    while (str[i])
    {
        j = 0;
        while (str[i][j])
        {
            tmp2 = realloc(tmp2, (j + 1));
            tmp2[j] = str[i][j];
            if (ft_strchr("$", str[i][j]) != NULL)
            {
                // if (str[i][j + 1] == '$')
                // {
                //     tmp2 = ft_strjoin(tmp2, ft_itoa(getpid()));
                //     j++;
                // }
                // else
                tmp2[j] = '\0';
                tmp = ft_strdup(&str[i][j + 1]);
                if (my_check_env(arg, tmp) != NULL)
                {
                    tmp = ft_strdup(my_check_env(arg, tmp));
                    (free(str[i]), str[i] = NULL);
                    str[i] = ft_strdup(ft_strjoin(tmp2, tmp));
                }
                free(tmp);
                //free(tmp2);
                break ;
            }
            j++;
        }
        i++;
    }
    
}