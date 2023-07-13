/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 23:58:55 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/13 18:13:03 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
	new->next = NULL;
}

void	ft_died1(t_philo	*ph)
{
	pthread_mutex_lock(&ph->data->mutex2);
	ph->data->loop = 0;
	pthread_mutex_unlock(&ph->data->mutex2);
	// pthread_mutex_lock(&ph->data->print_mutex);
	return ;
}

int	ft_died2(t_philo	*ph, time_t t)
{
	// pthread_mutex_lock(&ph->data->mutex2);
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
	// pthread_mutex_unlock(&ph->data->mutex2);
	return (0);
}
