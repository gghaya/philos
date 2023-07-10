/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 14:17:38 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/10 19:23:34 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	print_struct(t_philo *ph)
{
	int	i;

	i = 1;
	while (i <= 12)
	{
		printf("%d**%p\n", ph->id, ph->pid);
		ph = ph->next;
		i++;
	}
}

void	*thread_routine(void *philo)
{
	time_t	t;
	t_philo	*ph;

	ph = (t_philo *)philo;
	t = ph->data->init_tm;
	pthread_mutex_lock(&ph->mutex_meal);
	ph->lst_meal = gettime() - t;
	pthread_mutex_unlock(&ph->mutex_meal);
	if (ph->id % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&ph->fork);
		hendel_print("%lums %d has taken a fork\n", (gettime() - t), ph);
		pthread_mutex_lock(&ph->next->fork);
		hendel_print("%lums %d has taken a fork\n", (gettime() - t), ph);
		if(ph->data->must_eat != -1)
		{
			if(ph->nb_eat == ph->data->must_eat)
			{
				ph->data->check++;
			}
			ph->nb_eat++;
		}
		// lock_eat(ph);
		pthread_mutex_lock(&ph->mutex_meal);
		ph->lst_meal = gettime() - t;
		pthread_mutex_unlock(&ph->mutex_meal);
		hendel_print("%lums %d  is eating\n", (gettime() - t), ph);
		ft_usleep(ph->data->tm_eat);
		unlock_forks(ph, t);
	}
	return (NULL);
}

t_philo	*fillin_philos(int nbr, t_input *data)
{
	int			i;
	t_philo		*new;
	t_philo		*philo;
	t_philo		*first;

	i = 1;
	philo = NULL;
	while (i <= nbr)
	{
		new = ft_lstnew(data, i);
		if (i == 1)
			first = new;
		ft_lstadd_back(&philo, new);
		i++;
	}
	new->next = first;
	return (philo);
}

t_philo	*create_philo(t_philo *ph)
{
	int	i;
	int	j;

	i = 1;
	ph->data->init_tm = gettime();
	while (i <= ph->data->nb_philo)
	{
		j = pthread_create(&(ph->pid), NULL, &thread_routine, ph);
		if (j == -1)
			return (NULL);
		ph = ph->next;
		i++;
	}
	i = 1;
	while (i <= ph->data->nb_philo)
	{
		pthread_detach(ph->pid);
		ph = ph->next;
		i++;
	}
	return (ph);
}

int	main(int ac, char **av)
{
	t_input	*data;
	t_philo	*ph;

	ph = NULL;
	data = fillin_struct(ac, av);
	if (!data)
	{
		write(1, "Error\n", 6);
		free(data);
		return (0);
	}
	if (data->exit == -1 || data->i == -1 || data->j == -1
		|| data->must_eat == 0 || data->must_eat < -1)
	{
		write(1, "Error\n", 6);
		return (0);
	}
	ph = fillin_philos(ft_atoi(av[1]), data);
	ph = create_philo(ph);
	check_death(ph, gettime());
	destroy_philo(ph, data);
	return (0);
}
