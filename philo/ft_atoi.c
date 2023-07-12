/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:53:44 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/13 00:17:47 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	ft_atoi(const char *str)
{
	long long	n;
	long		pre;
	int			i;
	int			sign;

	i = 0 ;
	n = 0 ;
	sign = 1 ;
	if (str[i] == '-' || str[i] == '+')
		write_error();
	while (str[i] >= '0' && str[i] <= '9')
	{
		pre = n;
		n = n * 10 + str[i] - 48 ;
		if (pre != n / 10)
			write_error();
		i++;
	}
	return (ft_erreur(n, sign));
}

int	ft_erreur(long int n, int sign)
{
	if (n * sign < -2147483646 || n * sign > 2147483647)
	{
		return (-1);
	}
	return (n * sign);
}

int	write_error(void)
{
	return (-1);
}

int	ft_verification(const char *str, int i, int sign)
{
	if (str[i] == '-')
		sign = -1;
	if (str[i + 1] == '+' || str[i + 1] == '-' || str[i + 1] == 32
		|| str[i + 1] == '\0' || (str[i + 1] >= 9 && str[i + 1] <= 13))
		write_error ();
	return (sign);
}
