/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:10:00 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/30 18:00:29 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*lifecycle(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->n % 2 == 0)
		time_activity(philo->rules->time_to_eat, philo);
	if (philo->rules->n_meals != -1)
	{
		while (!check_death(philo) && !check_enough(philo))
		{
			// if (check_death(philo))
			// 	break ;
			taking_fork(philo);
			eating(philo);
			sleeping(philo);
			thinking(philo);
		}
	}
	else
	{
		while (!check_death(philo))
		{
			// if (check_death(philo))
			// 	break ;
			taking_fork(philo);
			eating(philo);
			sleeping(philo);
			thinking(philo);
		}
	}
	return (NULL);
}

void	taking_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->dealing_with_forks);
	if (philo->rules->n_philo != 1)
		multiple_philos_scenario(philo);
	else
	{
		pthread_mutex_lock(&philo->rules->forks[philo->n]);
		message(philo, 'f');
	}
	pthread_mutex_unlock(&philo->rules->dealing_with_forks);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->eating);
	message(philo, 'e');
	philo->meal_count += 1;
	if (philo->rules->n_meals != -1)
	{
		printf("WTFFFFFF\n");
		if (check_enough(philo))
		{
			pthread_mutex_lock(&philo->rules->protecting_enough);
			philo->rules->eaten_enough = 1;
			printf("WTF eaten_enough = %d\n", philo->rules->eaten_enough);
			pthread_mutex_unlock(&philo->rules->protecting_enough);
		}
	}
	philo->last_meal = timestamp();
	time_activity(philo->rules->time_to_eat, philo);
	if (philo->rules->n_philo != 1)
	{
		if (philo->n == philo->rules->n_philo - 1)
			pthread_mutex_unlock(&philo->rules->forks[0]);
		else
			pthread_mutex_unlock(&philo->rules->forks[philo->n + 1]);
	}
	pthread_mutex_unlock(&philo->rules->forks[philo->n]);
	pthread_mutex_unlock(&philo->rules->eating);
}

void	sleeping(t_philo *philo)
{
	message(philo, 's');
	time_activity(philo->rules->time_to_sleep, philo);
}

void	thinking(t_philo *philo)
{
	message(philo, 't');
}
