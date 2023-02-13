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

int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_int(char *str, int i)
{
	if (!is_digit(str[i]))
		return (1);
	i++;
	while (str[i])
	{
		if (!is_digit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_overflow(long long num)
{
	if (num > 2147483647)
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int			i;
	int			sign;
	long long	result;

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
	if (is_int(str, i))
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	if (check_overflow(result * sign))
		return (-1);
	return (result * sign);
}
