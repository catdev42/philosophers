/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:54:31 by myakoven          #+#    #+#             */
/*   Updated: 2024/04/29 19:22:35 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "philosophers.h"

typedef struct s_fork
{
    pthread_mutex_t *forks;
    
}	t_fork;

int	main(int argc, char **argv)
{
	int			i;
	int			num_philo;
	pthread_t	*philosopher_ids;

	if (argc < 2)
	{
		fprintf(2, "Too few args");
		return (1);
	}
	num_philo = atol(argv[1]);
	if (num_philo > INT_MAX || num_philo < 1)
	{
		fprintf(2, "Too or too many philosophers, sorry");
		return (2);
	}
	philosopher_ids = calloc((num_philo + 1), sizeof(pthread_t));
	if (!philosopher_ids)
	{
		fprintf(2, "Problems with malloc");
		return (3);
	}
	philosopher_ids[num_philo] = NULL;
	while (i < num_philo)
	{
		pthread_create(&philosopher_ids[i], NULL, FUNCTION, STRUCT);
		i++;
		if (i >= num_philo)
			i = i - num_philo;
		pthread_create(&philosopher_ids[i], NULL, OTHER_FUNCTION, STRUCT);
		i++;
		if (i >= num_philo)
			i = i - num_philo;
	}
}
