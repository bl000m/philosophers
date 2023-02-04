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

void	creating_philosophers(t_rules *data)
{
	int	i;

	i = 1;
	if (pthread_mutex_init(&data->philo->message_out, NULL))
		error_manager(3, data);
	if (pthread_mutex_init(&data->philo->eating, NULL))
		error_manager(3, data);
	if (pthread_mutex_init(&data->philo->sleeping, NULL))
		error_manager(3, data);
	while (i <= data->n_philo)
	{
		data->philo[i].rules = data;
		data->philo[i].n = i;
		data->philo[i].is_dead = 0;
		data->philo[i].meal_count = 0;
		data->philo[i].start = timestamp();
		data->philo[i].last_meal = data->philo[i].start;
		pthread_mutex_init(&data->philo[i].fork_left, NULL);
		if (data->n_philo > 1)
			pthread_mutex_init(&data->philo[i].fork_right, NULL);
		if (pthread_create(&data->philo[i].life, NULL,
				&lifecycle, &(data->philo[i])) != 0)
			error_manager(4, data);
		i++;
	}
	i = 1;
	while (i <= data->n_philo)
	{
		if (pthread_join(data->philo[i].life, NULL) != 0)
			error_manager(5, data);
		i++;
	}
}

void	*lifecycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// if (philo->rules->n_philo % 2 == 0)
	// 	time_activity(philo->rules->time_to_eat / 10);
	while (!philo->is_dead)
	{
		taking_fork(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
		//check+if+died
		//check if n meals max got
		// if (philo->meal_count == philo->rules->n_meals)
		// 	break ;
	}
	return (0);
}

int	philo_is_dead(t_philo *philo)
{
	if (philo->is_dead == 1)
		return (1);
	return (0);
}

void	taking_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_left);
	message(philo, 'f');
	if (philo->rules->n_philo > 1)
	{
		pthread_mutex_lock(&philo->fork_right);
		message(philo, 'f');
	}
}

void	eating(t_philo *philo)
{
	// if ((int)(timestamp() - philo->last_meal) > philo->rules->time_to_die)
	// 	philo->is_dead = 1;
	pthread_mutex_lock(&philo->eating);
	philo->last_meal = timestamp();
	philo->meal_count += 1;
	message(philo, 'e');
	time_activity(philo->rules->time_to_eat);
	pthread_mutex_unlock(&philo->eating);
	pthread_mutex_unlock(&philo->fork_left);
	if (philo->n > 1)
		pthread_mutex_unlock(&philo->fork_right);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->sleeping);
	message(philo, 's');
	time_activity(philo->rules->time_to_sleep);
	pthread_mutex_unlock(&philo->sleeping);
}

void	thinking(t_philo *philo)
{
	message(philo, 't');
}



