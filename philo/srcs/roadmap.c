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
	//creating philo/threads depending on argv[1]
	//creating and protect forks depending on argv[1]
	//creating state changes of philosophers lifetime:
	//loop threads calling routine func(sleep, eat, think)
	//check_if_need_to_die =>
	//parsing
	free_all(data);
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
	if (philo->n > 1)
	{
		pthread_mutex_lock(&philo->fork_right);
		message(philo, 'f');
	}
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->eating);
	message(philo, 'e');
	pthread_mutex_unlock(&philo->fork_left);
	if (philo->n > 1)
		pthread_mutex_unlock(&philo->fork_right);
	pthread_mutex_unlock(&philo->eating);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->sleeping);
	message(philo, 's');
	pthread_mutex_unlock(&philo->sleeping);
}

void	*lifecycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// while (!philo->is_dead)
	// {
		taking_fork(philo);
		eating(philo);
		sleeping(philo);
		//thinking(philo);
	// }
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
		data->philo[i].n = i;
		data->philo->is_dead = 0;
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

