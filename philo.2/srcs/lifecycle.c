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
	if (philo->n % 2 == 0 && philo->rules->n_philo != 1)
		time_activity(philo->rules->time_to_eat, philo);
	if (philo->rules->n_philo == 1)
	{
		taking_fork(philo);
		time_activity((philo->rules->time_to_die - timestamp()), philo);
		pthread_mutex_unlock(&philo->rules->forks[philo->n]);
		message(philo, 'd');
		philo->rules->someone_is_dead = 1;
	}
	else
	{
		if (philo->rules->n_meals != -1)
		{
			while (!check_death(philo) && !check_enough(philo))
			{
				activities(philo);
				time_activity((philo->rules->time_to_die - timestamp()), philo);
				check_death(philo);
			}
		}
		else
		{
			while (!check_death(philo))
			{
				activities(philo);
				time_activity((philo->rules->time_to_die - timestamp()), philo);
				check_death(philo);
			}
		}
	}
	return (NULL);
}
