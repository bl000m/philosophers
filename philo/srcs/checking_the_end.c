/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_the_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:25:14 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/30 17:05:14 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->dying);
	if ((timestamp() - philo->last_meal) > (t_time)philo->rules->time_to_die)
	{
		pthread_mutex_unlock(&philo->rules->dying);
		message(philo, 'd');
		philo->rules->someone_is_dead = 1;
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->dying);
	return (0);
}

int	check_enough(t_philo *philo)
{
	int	i;
	int	done;
	int	meals_count;

	i = 0;
	done = 0;
	while (i < philo->rules->n_philo)
	{
		counting_meals(&meals_count, philo, i);
		if (meals_count >= philo->rules->n_meals)
		{
			philo_done(&done, philo);
			if (done == philo->rules->n_philo)
			{
				pthread_mutex_lock(&philo->rules->protecting_enough);
				philo->rules->eaten_enough = 1;
				pthread_mutex_unlock(&philo->rules->protecting_enough);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	counting_meals(int *meals_count, t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->rules->counting);
	*meals_count = philo->rules->philo[i].meal_count;
	pthread_mutex_unlock(&philo->rules->counting);
}

void	philo_done(int *done, t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->checking_done);
	*done += 1;
	pthread_mutex_unlock(&philo->rules->checking_done);
}
