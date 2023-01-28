/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roadmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:10:00 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/28 16:39:35 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	t_philo			*data;

	check_error(argc);
	data = init_data(argc, argv);
	creating_philosophers(data);
	//creating philo/threads depending on argv[1]
	//creating and protect forks depending on argv[1]
	//creating state changes of philosophers lifetime:
	//loop threads calling routine func(sleep, eat, think)
	//check_if_need_to_die =>
	//parsing
	pthread_mutex_destroy(&data->mutex_philo);
	return (0);
}

void	*lifecycle(void *arg)
{
	int	philo_x;

	philo_x = *(int *)arg;
	// pthread_mutex_lock(&data->mutex_philo);
	printf("%llu: philo n.%d has taken a fork\n", get_timestamp(), philo_x);
	// pthread_mutex_unlock(&data->mutex_philo);
	free(arg);
	return (0);
}

void	creating_philosophers(t_philo *data)
{
	pthread_t philo[data->n_philo];
	int	i;
	int	*philo_x;

	i = 1;
	while (i <= data->n_philo)
	{
		philo_x = malloc(sizeof(int));
		*philo_x = i;
		if (pthread_create(&philo[i], NULL, &lifecycle, philo_x) != 0)
		{
			perror("failed to create philo");
			// free all
			exit(1);
		}
		i++;
	}
	i = 1;
	while (i <= data->n_philo)
	{
		if (pthread_join(philo[i], NULL) != 0)
		{
			perror("failed to ?");
			// free all ?
			exit(1);
		}
		i++;
	}
}

