/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:22:06 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/30 13:54:33 by mpagani          ###   ########lyon.fr   */
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
	data->philo->start = timestamp();
	if (argc == 6)
		data->n_meals = ft_atoi(argv[5]);
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!(data->philo))
		error_manager(2);
	// else if (argc == 5)
	// 	data->n_meals = ;
	pthread_mutex_init(&data->philo->mutex_fork, NULL);
	return (data);
}
