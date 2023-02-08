/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:49:34 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/30 18:00:03 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_all(t_rules *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		// free(&data->philo[i]);
		i++;
	}
	pthread_mutex_destroy(&data->message_out);
	pthread_mutex_destroy(&data->eating);
	// pthread_mutex_destroy(&data->philo->sleeping);
	free(data->philo);
	free(data->forks);
	free(data);
}
