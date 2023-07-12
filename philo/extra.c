/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 11:47:10 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/13 00:06:53 by gghaya           ###   ########.fr       */
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

void	check_death(t_philo *ph)
{
	time_t	t;
	int		i;

	i = 1;
	t = ph->data->init_tm;
	while (ph->data->loop)
	{
		usleep(100);
		// pthread_mutex_lock(&ph->data->check_mutex);
		if (ph->data->must_eat != -1)
		{
			// while (i <= ph->data->nb_philo)
			// {
				// if (ph->nb_eat < ph->data->must_eat)
				// 	ph = ph->next;

				if(ph->data->check == ph->data->nb_philo)
				{
				// printf("%d  ********* %d\n",ph->id,ph->nb_eat);
					pthread_mutex_lock(&ph->data->mutex1);
					ph->data->loop = 0;
					pthread_mutex_unlock(&ph->data->mutex1);
					pthread_mutex_lock(&ph->data->print_mutex);
					return;
				}
				// i++;
			// }



			// i = 1;
		}
		else
		{
			pthread_mutex_lock(&ph->data->mutex2);
			// printf("##########%d#########\n",ph->data->loop);
			if (gettime() - ph->lst_meal > ph->data->tm_die)
			{
				pthread_mutex_unlock(&ph->data->mutex2);
				pthread_mutex_lock(&ph->data->print_mutex);
				printf("%lu %d died\n", gettime() - t, ph->id);
				pthread_mutex_lock(&ph->data->mutex1);
				ph->data->loop = 0;
				pthread_mutex_unlock(&ph->data->mutex1);
			}
			pthread_mutex_unlock(&ph->data->mutex2);
		}
		// pthread_mutex_unlock(&ph->data->check_mutex);
	}
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
