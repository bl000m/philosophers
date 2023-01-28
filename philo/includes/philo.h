/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:10:36 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/28 16:37:07 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* libraries */
# include <stdio.h> // printf
# include <stdlib.h> //exit
# include <pthread.h> // creating threads
#include <sys/time.h> // timestamp

typedef unsigned long long int	t_time;

typedef struct s_philo
{
	pthread_mutex_t	mutex_philo;
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_meals;
}	t_philo;

/* functions */

/* settings */
t_philo	*init_data(int argc, char *argv[]);

/* philosophers lifecycle */
void	creating_philosophers(t_philo *data);
void	*lifecycle(void *arg);

/* utils */
int		ft_atoi(char *str);
t_time	get_timestamp(void);

/* error management */
void	check_error(int argc);

/* memory stuff */

#endif
