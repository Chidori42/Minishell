/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:20:53 by bramzil           #+#    #+#             */
/*   Updated: 2024/03/27 00:12:07 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define MAX 922337203685477580

long	ft_atoi(const char *str)
{
	long long			result;
	int					sign;

	result = 0;
	sign = 1;
	while ((9 <= *str && *str <= 13) || (*str == 32))
		str++;
	if (((*str == '-') || (*str == '+')))
		sign = 1 - 2 * (*str++ == '-');
	while (*str && *str == '0')
		str++;
	while (ft_isdigit(*str))
	{
		if ((result > MAX) || ((result == MAX) && ((*str - 48) > 7)))
			return (-1 * (sign > 0));
		result = result * 10 + (*str - 48);
		str++;
	}
	return (sign * result);
}
