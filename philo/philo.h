/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gghaya <gghaya@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 20:01:38 by gghaya            #+#    #+#             */
/*   Updated: 2023/07/10 18:54:51 by gghaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include "limits.h"
# include<sys/time.h>

typedef struct s_input
{
	int				nb_philo;
	int				tm_die;
	int				tm_eat;
	int				tm_sleep;
	int				must_eat;
	int				check;
	int				loop;
	time_t			init_tm;
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	mutex_loop;
	pthread_mutex_t	print_mutex;
	int				exit;
	int				i;
	int				j;
}				t_input;

typedef struct s_philo
{
	int				id;
	t_input			*data;
	pthread_t		pid;
	pthread_mutex_t	fork;
	struct s_philo	*next;
	time_t			lst_meal;
	pthread_mutex_t	mutex_meal;
	int				nb_eat;
}				t_philo;

int		write_error(void);
int		ft_atoi(const char *str);
int		ft_erreur(long int n, int sign);
int		check(int c, char **v);
int		ft_isdigit(char *s);
t_input	*fillin_struct(int ac, char **av);
void	print_struct(t_philo *ph);
t_philo	*fillin_philos(int nbr, t_input *data);
t_philo	*ft_lstnew(t_input *data, int id);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo	*create_philo(t_philo *ph);
void	*thread_routine(void *ph);
time_t	gettime(void);
void	check_death(t_philo *ph, time_t start);
void	ft_usleep(int tm);
void	hendel_print(char *s, time_t t, t_philo *ph);
int		nbr_eat(t_philo *p);
void	destroy_philo(t_philo *ph, t_input *data);
void	lock_eat(t_philo *ph);
void	unlock_forks(t_philo *ph, time_t t);
t_input	*fill(t_input *dt, int ac, char **av);
int		fct(t_philo *ph, time_t t);
void	ft_lstclear(t_philo **lst);

#endif