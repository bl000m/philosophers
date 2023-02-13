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

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define GREEN "\x1b[32m"
# define RED "\x1b[41m"
# define NORMAL "\x1b[m"

typedef unsigned long long int	t_time;
typedef struct s_rules			t_rules;
typedef struct s_philo			t_philo;

struct s_philo
{
	pthread_t		life;
	int				n;
	int				meal_count;
	t_time			start;
	t_time			last_meal;
	t_rules			*rules;
};

struct s_rules
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_meals;
	int				eaten_enough;
	int				someone_is_dead;
	pthread_mutex_t	message_out;
	pthread_mutex_t	dealing_with_forks;
	pthread_mutex_t	protecting_enough;
	pthread_mutex_t	checking_done;
	pthread_mutex_t	eating;
	pthread_mutex_t	counting;
	pthread_mutex_t	dying;
	pthread_mutex_t	*forks;
	t_philo			*philo;

};

/* settings */
t_rules	*init_data(int argc, char *argv[]);
void	init_philo(t_philo *philo, t_rules *data, int i);
void	init_mutex(t_rules *data);

/* philosophers lifecycle */
void	creating_philosophers(t_rules *data);
void	create_life(t_philo *philo, t_rules *data);
void	*lifecycle(void *arg);
void	activities(t_philo *philo);
void	taking_fork(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
int		check_death(t_philo *philo);
int		check_enough(t_philo *philo);
void	counting_meals(int *meals_count, t_philo *philo, int i);
void	lock_order(t_philo *philo, pthread_mutex_t *left_fork,
			pthread_mutex_t *right_fork);
void	multiple_philos_scenario(t_philo *philo);
void	philo_done(int *done, t_philo *philo);

/* time management */
t_time	timestamp(void);
t_time	timestamp_delta(t_philo *philo);
void	message(t_philo *philo, char flag);
void	time_activity(t_time millisec, t_philo *philo);

/* utils */
int		ft_atoi(char *str);
int		is_digit(int c);
int		is_int(char *str, int i);
int		check_overflow(long long num);

/* error management */
int		check_error(int argc, char *argv[]);
void	error_manager(int error, t_rules *data);

/* memory stuff */
void	free_all(t_rules *data);

#endif
