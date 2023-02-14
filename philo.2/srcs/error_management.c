/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:25:14 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/30 17:05:14 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_error(int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
	{
		printf("n. of arguments incorrect\n");
		return (1);
	}
	if (argc == 6 && ft_atoi(argv[5]) == 0)
	{
		printf("n. of meals set not allowing a philo to live even a sec\n");
		return (1);
	}
	if ((ft_atoi(argv[1]) < 0 || ft_atoi(argv[2]) < 0
			|| ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
		|| (argc == 6 && ft_atoi(argv[5]) < 0))
	{
		printf("arg not valid detected\n");
		return (1);
	}
	return (0);
}

void	error_manager(int error, t_rules *data)
{
	if (error == 2)
		printf("error allocating memory\n");
	if (error == 3)
		printf("error initializing the message_out feature\n");
	if (error == 4)
		printf("error creating a philosopher/thread\n");
	if (error == 5)
		printf("error joining a philosopher/thread\n");
	free_all(data);
}
