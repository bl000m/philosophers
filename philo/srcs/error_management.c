/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:25:14 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/28 13:48:57 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_error(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("n. of arguments incorrect");
		exit(1);
	}
}
