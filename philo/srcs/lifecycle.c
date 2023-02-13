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

	pthread_mutex_lock(&philo->rules->message_out);
	pthread_mutex_unlock(&philo->rules->message_out);
	philo->last_meal = philo->rules->start;

	if (philo->n % 2 == 0)
		time_activity(philo->rules->time_to_eat, philo);
	if (philo->rules->n_meals != -1)
	{
		while (!check_death(philo) && !check_enough(philo))
		{
			// printf("delta philo %d = %ld\n", philo->n + 1, (long)(timestamp() - philo->last_meal));
			activities(philo);
		}
	}
	else
	{
		while (!check_death(philo))
		{
			// printf("delta philo %d = %ld\n", philo->n + 1, (long)(timestamp() - philo->last_meal));
			activities(philo);
		}
	}
	return (NULL);
}
