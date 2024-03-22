/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:56:01 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/03/20 18:14:58 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    parcing(t_data *arg)
{
    int     i;
    int     j;
    char    *str;
    char    *tmp;

    i = 0;
    tmp = NULL;
    while (arg->str[i] && arg->str)
    {
        j = i + 1;
        while (arg->str[i] == ' ' && arg->str[i])
            i++;
        while (arg->str[j] && !ft_strchr("|;", arg->str[j]))
            j++;
        str = ft_substr(arg->str, i, j - i);
        tmp = ft_strjoin(tmp, str);
        tmp = ft_strjoin(tmp, "\n");
        free(str);
        i = j;
    }
    //printf("--%s--\n", tmp);
    arg->cmds = ft_split(tmp, '\n');
    free(tmp);
}
