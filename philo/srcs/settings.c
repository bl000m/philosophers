/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:22:06 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/30 17:59:34 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_rules	*init_data(int argc, char *argv[])
{
	t_rules	*data;

	data = malloc(sizeof(*data));
	data->n_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->n_meals = -1;
	if (argc == 6)
		data->n_meals = ft_atoi(argv[5]);
	data->philo = malloc(sizeof(t_philo) * (data->n_philo));
	if (!(data->philo))
		error_manager(2, data);
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->n_philo));
	if (!(data->philo))
		error_manager(2, data);
	if (pthread_mutex_init(&data->philo->message_out, NULL))
		error_manager(3, data);
	if (pthread_mutex_init(&data->philo->eating, NULL))
		error_manager(3, data);
	if (pthread_mutex_init(&data->philo->sleeping, NULL))
		error_manager(3, data);
	return (data);
}

void	init_philo(t_philo *philo, t_rules *data, int i)
{
	philo->rules = data;
	philo->n = i;
	philo->is_dead = 0;
	philo->meal_count = 0;
	philo->start = timestamp();
	philo->last_meal = philo->start;
}
