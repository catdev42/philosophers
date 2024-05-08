/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:04:04 by myakoven          #+#    #+#             */
/*   Updated: 2024/05/01 20:00:05 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
    t_table table;
    
	if (!(argc >= 5 && argc <= 6))
	{
		fprintf(2, "./fdf num_philo todie toeat tosleep"); //illegal
		return (1);
	}

    // error checking, filling table with info
    parse_input(&table, argv);
    // mallocing etc
    data_init(&table);
    //
    dinner_start(&table);
    // if max meals reached or 1 philo dies
    clean(&table);
}
