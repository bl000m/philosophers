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

t_time	timestamp(void)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return ((timestamp.tv_sec * 1000) + (timestamp.tv_usec / 1000));
}

t_time	timestamp_delta(t_philo *philo)
{
	return (timestamp() - philo->start);
}

void	message(t_philo *philo, char flag)
{
	pthread_mutex_lock(&philo->message_out);
	if (flag == 'f')
		printf("%09llu: philo n.%d has taken a fork\n",
			timestamp_delta(philo), philo->n);
	else if (flag == 'e')
		printf("%09llu: philo n.%d is eating\n",
			timestamp_delta(philo), philo->n);
	else if (flag == 's')
		printf("%09llu: philo n.%d is sleeping\n",
			timestamp_delta(philo), philo->n);
	else if (flag == 't')
		printf("%09llu: philo n.%d is thinking\n",
			timestamp_delta(philo), philo->n);
	pthread_mutex_unlock(&philo->message_out);
}

// check better how many microsec to usleep
void	time_activity(t_time millisec)
{
	t_time	start;

	start = timestamp();
	while (timestamp() - start < millisec)
		usleep(100);
}
