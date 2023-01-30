/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:10:36 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/30 13:52:03 by mpagani          ###   ########lyon.fr   */
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
	pthread_t		life;
	int				n;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	fork_right;
	pthread_mutex_t	mutex_fork;
	t_time			start;
}	t_philo;

typedef struct s_rules
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_meals;
	t_philo			*philo;
}	t_rules;

/* functions */

/* settings */
t_rules	*init_data(int argc, char *argv[]);

/* philosophers lifecycle */
void	creating_philosophers(t_rules *data);
void	*lifecycle(void *arg);

/* utils */
int		ft_atoi(char *str);
t_time	timestamp(void);
t_time	timestamp_delta(t_philo *philo);

/* error management */
void	check_error(int argc, char *argv[]);
void	error_manager(int	error);

/* memory stuff */

#endif
