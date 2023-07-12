/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:50:21 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/12 22:52:38 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	unlock_forks(t_philo *ph, time_t t)
{
	pthread_mutex_unlock(&ph->fork);
	pthread_mutex_unlock(&ph->next->fork);
	hendel_print("%lums %d is sleeping\n", (gettime() - t), ph);
	ft_usleep(ph->data->tm_sleep);
	hendel_print("%lums %d is thinking\n", (gettime() - t), ph);
	return ;
}

void	lock_eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->data->mutex_eat);
	ph->nb_eat++;
	pthread_mutex_unlock(&ph->data->mutex_eat);
	return ;
}

void	destroy_philo(t_philo *ph, t_input *data)
{
	int		i;
	t_philo	*p;

	i = 1;
	p = NULL;
	pthread_mutex_destroy(&ph->data->mutex_eat);
	pthread_mutex_destroy(&ph->data->print_mutex);
	pthread_mutex_destroy(&ph->data->mutex1);
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
	pthread_mutex_init(&dt->mutex1, NULL);
	pthread_mutex_init(&dt->mutex2, NULL);
	return (dt);
}
