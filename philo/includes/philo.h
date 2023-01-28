/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:10:36 by mpagani           #+#    #+#             */
/*   Updated: 2023/01/28 13:14:03 by mpagani          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* libraries */
# include <stdio.h>
# include <stdlib.h>
/* struct */
typedef struct s_philo
{
	int	n_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
}	t_philo;

/* functions */

/* settings */
t_philo	*init_data(char *argv[]);

/* parsing */

/* utils */
int		ft_atoi(char *str);

/* error management */
void	check_error(int argc);

/* memory stuff */

#endif
