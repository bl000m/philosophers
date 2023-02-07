/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:10:36 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/30 17:58:54 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* libraries */
# include <stdio.h> // printf
# include <unistd.h> // usleep
# include <stdlib.h> //exit
# include <pthread.h> // creating threads
# include <sys/time.h> // timestamp

#define GREEN "\x1b[32m"
#define NORMAL "\x1b[m"

typedef unsigned long long int	t_time;
typedef struct s_rules			t_rules;
typedef struct s_philo			t_philo;

struct s_philo
{
	pthread_t		life;
	int				n;
	// pthread_mutex_t	fork_left;
	// pthread_mutex_t	fork_right;
	int				is_dead;
	struct s_rules	*rules;
	pthread_mutex_t	message_out;
	pthread_mutex_t	eating;
	pthread_mutex_t	sleeping;
	t_time			start;
	t_time			last_meal;
	int				meal_count;
};

struct s_rules
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_meals;
	pthread_mutex_t	*forks;
	t_philo			*philo;

};

/* functions */

/* settings */
t_rules	*init_data(int argc, char *argv[]);
void	init_philo(t_philo *philo, t_rules *data, int i);

/* philosophers lifecycle */
void	creating_philosophers(t_rules *data);
void	create_life(t_philo *philo, t_rules *data);
void	waiting_life_finished(pthread_t life, t_rules *data);
void	*lifecycle(void *arg);
int		philo_is_dead(t_philo *philo);
void	taking_fork(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

/* utils */
int		ft_atoi(char *str);
t_time	timestamp(void);
t_time	timestamp_delta(t_philo *philo);
void	message(t_philo *philo, char flag);
void	time_activity(t_time millisec);

/* error management */
void	check_error(int argc, char *argv[]);
void	error_manager(int	error, t_rules *data);

/* memory stuff */
void	free_all(t_rules *data);

#endif
