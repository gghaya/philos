/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 11:47:10 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/13 14:37:02 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

time_t	gettime(void)
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return ((cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000));
}


void	check_death(t_philo *ph)
{
	time_t	t;

	t = ph->data->init_tm;
	pthread_mutex_lock(&ph->data->mutex2);
	while (ph->data->loop)
	{
		pthread_mutex_unlock(&ph->data->mutex2);

		usleep(100);
		pthread_mutex_lock(&ph->data->check_mutex);
		if (ph->data->must_eat != -1 && ph->data->check == ph->data->nb_philo)
		{
			pthread_mutex_unlock(&ph->data->check_mutex);
			return (ft_died1(ph));
		}
		else
			ft_died2(ph, t);
		pthread_mutex_unlock(&ph->data->check_mutex);
		// pthread_mutex_unlock(&ph->data->mutex3);
	}
	// pthread_mutex_unlock(&ph->data->mutex1);
}