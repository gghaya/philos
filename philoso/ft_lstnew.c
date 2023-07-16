/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 23:07:09 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/14 07:53:40 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"
#include<stdio.h>

t_philo	*ft_lstnew(t_input *data, int id)
{
	t_philo	*list;

	list = (t_philo *)malloc(sizeof(t_philo));
	if (!list)
		return (NULL);
	list->id = id;
	list->data = data;
	list->nb_eat = 0;
	list->lst_meal = 0;
	list->next = NULL;
	pthread_mutex_init(&list->fork, NULL);
	pthread_mutex_init(&list->mutex_meal, NULL);
	return (list);
}

void	ft_lstclear(t_philo **lst)
{
	t_philo	*p;
	int		nb_philo;
	int		i;

	nb_philo = (*lst)->data->nb_philo;
	i = 1;
	if (!lst || !*lst)
		return ;
	while (i <= nb_philo)
	{
		p = (*lst)->next;
		pthread_mutex_destroy(&(*lst)->fork);
		pthread_mutex_destroy(&(*lst)->mutex_meal);
		free((*lst));
		(*lst) = p;
		i++;
	}
}

void	ft_eat(t_philo	*ph, time_t t)
{
	pthread_mutex_lock(&ph->data->mutex2);
	if (ph->data->loop == 1)
	{
		pthread_mutex_unlock(&ph->data->mutex2);
		pthread_mutex_lock(&ph->fork);
		pthread_mutex_lock(&ph->data->print_mutex);
		printf("%lu %d has taken a fork\n", gettime() - t, ph->id);
		pthread_mutex_unlock(&ph->data->print_mutex);
		pthread_mutex_lock(&ph->data->mutex2);
	}
	pthread_mutex_unlock(&ph->data->mutex2);
	pthread_mutex_lock(&ph->data->mutex2);
	if (ph->data->loop == 1)
	{
		pthread_mutex_unlock(&ph->data->mutex2);
		pthread_mutex_lock(&ph->next->fork);
		pthread_mutex_lock(&ph->data->print_mutex);
		printf("%lu %d has taken a fork\n", gettime() - t, ph->id);
		pthread_mutex_unlock(&ph->data->print_mutex);
		pthread_mutex_lock(&ph->data->mutex2);
	}
	pthread_mutex_unlock(&ph->data->mutex2);
	eat_print(ph, t);
	return ;
}

void	ft_sleep(t_philo	*ph, time_t	t)
{
	if (ph->data->must_eat != -1)
	{
		pthread_mutex_lock(&ph->data->mutex_eat);
		ph->nb_eat++;
		pthread_mutex_unlock(&ph->data->mutex_eat);
	}
	if (ph->nb_eat == ph->data->must_eat)
	{
		pthread_mutex_lock(&ph->data->check_mutex);
		ph->data->check++;
		pthread_mutex_unlock(&ph->data->check_mutex);
	}
	ft_usleep(ph->data->tm_eat);
	pthread_mutex_unlock(&ph->fork);
	pthread_mutex_unlock(&ph->next->fork);
	pthread_mutex_lock(&ph->data->print_mutex);
	printf("%lu %d is sleeping\n", gettime() - t, ph->id);
	pthread_mutex_unlock(&ph->data->print_mutex);
	ft_usleep(ph->data->tm_sleep);
	return ;
}
