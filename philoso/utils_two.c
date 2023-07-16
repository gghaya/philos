/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:50:21 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/14 11:13:02 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	destroy_philo(t_philo *ph, t_input *data)
{
	int		i;
	t_philo	*p;

	i = 1;
	p = NULL;
	pthread_mutex_destroy(&ph->data->mutex_eat);
	pthread_mutex_destroy(&ph->data->print_mutex);
	pthread_mutex_destroy(&ph->data->mutex2);
	free(data);
	ft_lstclear(&ph);
	return ;
}

t_input	*fill(t_input *dt, int ac, char **av)
{
	dt->exit = check(ac, av);
	if (dt->exit == -1)
		return (free(dt), NULL);
	dt->nb_philo = ft_atoi(av[1]);
	dt->tm_die = ft_atoi(av[2]);
	dt->tm_eat = ft_atoi(av[3]);
	dt->tm_sleep = ft_atoi(av[4]);
	dt->loop = 1;
	dt->check = 0;
	pthread_mutex_init(&dt->print_mutex, NULL);
	pthread_mutex_init(&dt->mutex_eat, NULL);
	pthread_mutex_init(&dt->check_mutex, NULL);
	pthread_mutex_init(&dt->mutex2, NULL);
	return (dt);
}

void	check_death(t_philo *ph)
{
	time_t	t;

	t = ph->data->init_tm;
	while (1)
	{
		usleep(100);
		pthread_mutex_lock(&ph->data->check_mutex);
		if (ph->data->must_eat != -1 && ph->data->check == ph->data->nb_philo)
		{
			pthread_mutex_unlock(&ph->data->check_mutex);
			return (died_eat(ph));
		}
		else
		{
			if (died_time(ph, t))
				break ;
		}
		pthread_mutex_unlock(&ph->data->check_mutex);
	}
}

time_t	gettime(void)
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return ((cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000));
}

int	died_time(t_philo	*ph, time_t t)
{
	pthread_mutex_lock(&ph->mutex_meal);
	if (gettime() - ph->lst_meal > ph->data->tm_die)
	{
		pthread_mutex_lock(&ph->data->print_mutex);
		printf("%lu %d died\n", gettime() - t, ph->id);
		pthread_mutex_unlock(&ph->data->mutex2);
		pthread_mutex_lock(&ph->data->mutex2);
		ph->data->loop = 0;
		return (1);
		pthread_mutex_unlock(&ph->data->mutex2);
		pthread_mutex_unlock(&ph->mutex_meal);
	}
	pthread_mutex_unlock(&ph->mutex_meal);
	return (0);
}
