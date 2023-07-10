/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 23:07:09 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/10 21:50:43 by gghaya           ###   ########.fr       */
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
