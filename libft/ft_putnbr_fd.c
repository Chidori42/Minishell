/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 10:31:49 by bramzil           #+#    #+#             */
/*   Updated: 2023/11/04 13:36:19 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_digit(int n)
{
	size_t			cnt;

	cnt = 0;
	while (n && ++cnt)
		n /= 10;
	return (cnt);
}

void	ft_putnbr_fd(int n, int fd)
{
	long			nbr;
	bool			sign;
	char			str[12];
	size_t			dg_len;

	nbr = n;
	sign = false;
	if (nbr < 0)
		sign = true;
	nbr *= 1 - (2 * sign);
	dg_len = ft_count_digit(nbr) + (1 * sign) + (1 * (nbr == 0));
	str[0] = ('-' * sign) + ('0' * (nbr == 0));
	str[dg_len] = '\0';
	while (nbr)
	{
		str[--dg_len] = nbr % 10 + 48;
		nbr /= 10;
	}
	ft_putstr_fd(str, fd);
}
