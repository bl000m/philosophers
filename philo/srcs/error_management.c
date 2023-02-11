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

void	check_error(int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
	{
		printf("n. of arguments incorrect");
		exit(1);
	}
	if (argc == 6 && ft_atoi(argv[5]) == 0)
	{
		printf("n. of meals set not allowing a philo to live even a sec");
		exit(1);
	}
}

void	error_manager(int error, t_rules *data)
{
	if (error == 2)
		perror("error allocating memory");
	if (error == 3)
		perror("error initializing the message_out feature");
	if (error == 4)
		perror("error creating a philosopher/thread");
	if (error == 5)
		perror("error joining a philosopher/thread");
	free_all(data);
}
