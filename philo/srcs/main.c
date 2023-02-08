/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roadmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:10:00 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/30 18:00:29 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	t_rules			*data;

	check_error(argc, argv);
	data = init_data(argc, argv);
	creating_philosophers(data);
	free_all(data);
	return (0);
}

void	create_life(t_philo *philo, t_rules *data)
{
	if (pthread_create(&philo->life, NULL, &lifecycle, philo) != 0)
		error_manager(4, data);
}

void	creating_philosophers(t_rules *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		init_philo(&data->philo[i], data, i);
		pthread_mutex_init(&data->forks[i], NULL);
		create_life(&data->philo[i], data);
		i++;
	}
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_join(data->philo[i].life, NULL) != 0)
			error_manager(5, data);
		i++;
	}
}

void	*lifecycle(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->n % 2 == 0)
	{
		message(philo, 's');
		time_activity(philo->rules->time_to_eat);
	}
	while (1)
	{
		if ((timestamp() - philo->last_meal) > (t_time)philo->rules->time_to_die)
		{
			message(philo, 'd');
			free_all(philo->rules);
			exit(0);
		}
		taking_fork(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
		if (philo->rules->n_meals != -1)
		{
			if (philo->rules->eaten_enough == philo->rules->n_philo)
			{
				free_all(philo->rules);
				exit(0);
			}
		}
	}
	return (0);
}

void	taking_fork(t_philo *philo)
{
	if (philo->rules->n_philo != 1)
	{
		pthread_mutex_lock(&philo->rules->forks[philo->n]);
		message(philo, 'f');
		if (philo->rules->n_philo % 2 == 0)
			pthread_mutex_lock(&philo->rules->forks[philo->n + 1]);
		message(philo, 'f');
	}
	else
		message(philo, 'f');
	
}

void	eating(t_philo *philo)
{
	if (philo->rules->n_philo != 1)
	{
		pthread_mutex_lock(&philo->eating);
		message(philo, 'e');
		philo->meal_count += 1;
		if (philo->rules->n_meals != -1)
		{
			if (philo->meal_count >= philo->rules->n_meals 
					&& philo->rules->n_meals > 0)
				philo->rules->eaten_enough++;
		}
		philo->last_meal = timestamp();
		time_activity(philo->rules->time_to_eat);
		pthread_mutex_unlock(&philo->rules->forks[philo->n + 1]);
		pthread_mutex_unlock(&philo->rules->forks[philo->n]);
		pthread_mutex_unlock(&philo->eating);
	}
	else
	{
		message(philo, 'e');
		philo->meal_count += 1;
		time_activity(philo->rules->time_to_eat);
		philo->last_meal = timestamp();
	}

}

void	sleeping(t_philo *philo)
{
	// pthread_mutex_lock(&philo->sleeping);
	message(philo, 's');
	time_activity(philo->rules->time_to_sleep);
	// pthread_mutex_unlock(&philo->sleeping);
}

void	thinking(t_philo *philo)
{
	message(philo, 't');
}



