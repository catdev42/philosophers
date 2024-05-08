/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:00:24 by myakoven          #+#    #+#             */
/*   Updated: 2024/05/01 20:31:27 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	make_num(char *arg);

void	parse_input(t_table *table, char **argv)
{
	int	num_philo;

	table->philo_num = make_num(argv[1]);
	table->time_to_die = make_num(argv[2]) * 1000; // conver to
	table->time_to_eat = make_num(argv[3]) * 1000;
	table->time_to_die = make_num(argv[4]) * 1000;
	if (!table->philo_num || !table->time_to_die || !table->time_to_eat
		|| !table->time_to_die)
		error_exit("Wrong input, sorry");
	if (table->time_to_die < 60000 || table->time_to_eat < 60000
		|| !table->time_to_die)
		error_exit("Time must be more than 60");
	if (argv[5])
		table->num_limit_meals = make_num(argv[5]);
	else
		table->num_limit_meals = -1;
}

static long	make_num(char *arg)
{
	long	num;

	num = 0;
	num = ft_atol(arg);
	if (num > INT_MAX || num < 1)
		return (0);
	return (num);
}
