/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 23:58:55 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/05 18:31:40 by gghaya           ###   ########.fr       */
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
