/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 11:44:41 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/11 11:09:50 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	check(int c, char **v)
{
	if (c != 6 && c != 5)
		return (write_error());
	while (--c >= 1)
	{
		if (ft_isdigit(v[c]) == 0)
			return (write_error());
	}
	return (0);
}

int	ft_isdigit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

t_input	*fillin_struct(int ac, char **av)
{
	t_input	*dt;

	dt = malloc(sizeof(t_input));
	if (!dt)
		return (NULL);
	dt = fill(dt, ac, av);
	if (!dt)
		return (NULL);
	if (ac == 5)
	{
		dt->must_eat = -1;
	}
	else
		dt->must_eat = ft_atoi(av[5]);
	if (dt->nb_philo > 200 || dt->tm_die < 60
		|| dt->tm_eat < 60 || dt->tm_sleep < 60)
			dt->i = write_error();
	if (dt->nb_philo == 0 || dt->tm_die == 0
		|| dt->tm_eat == 0 || dt->tm_sleep == 0)
			dt->j = write_error();
	return (dt);
}

void	ft_usleep(int tm)
{
	time_t	now;

	now = gettime();
	while (gettime() < now + tm)
		usleep(100);
}

void	hendel_print(char *s, time_t t, t_philo *ph)
{
	pthread_mutex_lock(&ph->data->print_mutex);
	printf(s, t, ph->id);
	pthread_mutex_unlock(&ph->data->print_mutex);
}
