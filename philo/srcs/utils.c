/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 13:07:21 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/30 17:58:21 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	lock_order(t_philo *philo, pthread_mutex_t *left_fork,
			pthread_mutex_t *right_fork)
{
	pthread_mutex_lock(left_fork);
	message(philo, 'f');
	pthread_mutex_lock(right_fork);
	message(philo, 'f');
}

void	multiple_philos_scenario(t_philo *philo)
{
	if (philo->n == philo->rules->n_philo - 1)
	{
		if (&philo->rules->forks[philo->n] < &philo->rules->forks[0])
			lock_order(philo, &philo->rules->forks[philo->n],
				&philo->rules->forks[0]);
		else
			lock_order(philo, &philo->rules->forks[0],
				&philo->rules->forks[philo->n]);
	}
	else
	{
		if (&philo->rules->forks[philo->n]
			< &philo->rules->forks[philo->n + 1])
			lock_order(philo, &philo->rules->forks[philo->n],
				&philo->rules->forks[philo->n + 1]);
		else
			lock_order(philo, &philo->rules->forks[philo->n + 1],
				&philo->rules->forks[philo->n]);
	}
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}
