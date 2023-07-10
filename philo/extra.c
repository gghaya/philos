/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 11:47:10 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/10 21:46:35 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

time_t	gettime(void)
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return ((cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000));
}

int	nbr_eat(t_philo *p)
{
	int	i;

	i = 1;
	while (i <= p->data->nb_philo)
	{
		if (p->nb_eat < p->data->must_eat)
			return (0);
		p = p->next;
		i++;
	}
	return (1);
}

void	check_death(t_philo *ph, time_t start)
{
	time_t	t;

	t = ph->data->init_tm;
	while (1)
	{
		pthread_mutex_lock(&ph->data->mutex_eat);
		if (nbr_eat(ph) == 1 && ph->data->must_eat != -1)
		{
			pthread_mutex_lock(&ph->data->print_mutex);
			return ;
		}
		else if (fct(ph, gettime() - start) == 0)
			return ;
		ph = ph->next;
		pthread_mutex_unlock(&ph->mutex_meal);
	}
	return ;
}

int	fct(t_philo *ph, time_t t)
{
	pthread_mutex_unlock(&ph->data->mutex_eat);
	pthread_mutex_lock(&ph->mutex_meal);
	if (t - ph->lst_meal > ph->data->tm_die)
	{
		pthread_mutex_lock(&ph->data->print_mutex);
		printf("%lums %d died\n", t, ph->id);
		return (0);
	}
	return (1);
}
