/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-fagr <ael-fagr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:42:32 by ael-fagr          #+#    #+#             */
/*   Updated: 2024/03/18 00:37:49 by ael-fagr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_parameter(t_data *arg)
{
    arg->tab = NULL;
    arg->str = NULL;
    arg->envp = NULL;
    arg->tmp = NULL;
    arg->cmds = NULL;
    arg->opers = NULL;
    arg->sig = 0;
}