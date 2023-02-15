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

	if (check_error(argc, argv))
		return (0);
	data = init_data(argc, argv);
	creating_philosophers(data);
	free_all(data);
	return (0);
}

void	creating_philosophers(t_rules *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->time);
	data->start = timestamp();
	while (i < data->n_philo)
	{
		init_philo(&data->philo[i], data, i);
		pthread_mutex_lock(&data->dealing_with_forks);
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_unlock(&data->dealing_with_forks);
		create_life(&data->philo[i], data);
		i++;
	}
	data->start = timestamp();
	pthread_mutex_unlock(&data->time);
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_join(data->philo[i].life, NULL) != 0)
			error_manager(5, data);
		i++;
	}
}

void	create_life(t_philo *philo, t_rules *data)
{
	if (pthread_create(&philo->life, NULL, &lifecycle, philo) != 0)
		error_manager(4, data);
}
