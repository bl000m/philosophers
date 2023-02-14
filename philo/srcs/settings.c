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
	data->eaten_enough = 0;
	data->someone_is_dead = 0;
	if (argc == 6)
		data->n_meals = ft_atoi(argv[5]);
	data->philo = malloc(sizeof(t_philo) * (data->n_philo));
	if (!(data->philo))
		error_manager(2, data);
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->n_philo));
	if (!(data->forks))
		error_manager(2, data);
	init_mutex(data);
	return (data);
}

void	init_mutex(t_rules *data)
{
	pthread_mutex_init(&data->message_out, NULL);
	pthread_mutex_init(&data->dealing_with_forks, NULL);
	pthread_mutex_init(&data->protecting_enough, NULL);
	pthread_mutex_init(&data->eating, NULL);
	pthread_mutex_init(&data->dying, NULL);
	pthread_mutex_init(&data->counting, NULL);
	pthread_mutex_init(&data->checking_done, NULL);
}

void	init_philo(t_philo *philo, t_rules *data, int i)
{
	philo->rules = data;
	philo->life = 0;
	philo->n = i;
	pthread_mutex_lock(&philo->rules->counting);
	philo->meal_count = 0;
	pthread_mutex_unlock(&philo->rules->counting);
	// philo->start = timestamp();
	philo->last_meal = data->start;
}
