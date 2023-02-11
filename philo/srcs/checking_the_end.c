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
	if ((timestamp() - philo->last_meal) > (t_time)philo->rules->time_to_die)
	{
		message(philo, 'd');
		pthread_mutex_lock(&philo->rules->dying);
		philo->rules->someone_is_dead = 1;
		pthread_mutex_unlock(&philo->rules->dying);
		return (1);
	}
	return (0);
}

void	count_meals(t_philo *philo, int *meals_count)
{
	pthread_mutex_lock(&philo->rules->stop);
	*meals_count = philo->meal_count;
	pthread_mutex_unlock(&philo->rules->stop);
}

int	check_enough(t_philo *philo)
{
	int	i;
	int	done;
	int	meals_count;

	i = 0;
	done = 0;
	while (i++ < philo->rules->n_philo)
	{
		count_meals(philo, &meals_count);
		if (meals_count >= philo->rules->n_meals)
		{
			if (philo->n != 0)
			{
				if (++done == philo->rules->n_philo - 1)
					return (1);
			}
			else
			{
				if (++done == philo->rules->n_philo)
					return (1);
			}
		}
		usleep(50);
	}
	return (0);
}
