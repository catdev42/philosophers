/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:31:40 by myakoven          #+#    #+#             */
/*   Updated: 2024/05/01 20:43:27 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

data_init(t_table *table)
{
    table->end_simulation = false;
    table->philos = ft_calloc((table->philo_num +1), sizeof(t_philo));
    
}

static void handle_mutax_error(int status, )

void safe_mutex_handle(t_mutex){
    
}