/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:22:06 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/28 16:37:13 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*init_data(int argc, char *argv[])
{
	t_philo	*data;

	data = malloc(sizeof(*data));
	data->n_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->n_meals = ft_atoi(argv[5]);
	else if (argc == 5)
		data->n_meals = 0;
	pthread_mutex_init(&data->mutex_philo, NULL);
	return (data);
}
