/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:25:14 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/30 17:05:14 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	activities(t_philo *philo)
{
	taking_fork(philo);
	eating(philo);
	sleeping(philo);
	thinking(philo);
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
	pthread_mutex_lock(&philo->rules->counting);
	philo->meal_count += 1;
	pthread_mutex_unlock(&philo->rules->counting);
	if (philo->rules->n_meals != -1)
	{
		if (check_enough(philo))
		{
			pthread_mutex_lock(&philo->rules->protecting_enough);
			philo->rules->eaten_enough = 1;
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
