/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 21:41:46 by myakoven          #+#    #+#             */
/*   Updated: 2024/04/28 22:26:38 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdio.h>

#define TIMES_TO_COUNT 21000

typedef struct s_counter
{
	pthread_mutex_t	count_mutex;
	unsigned int	count;
}					t_counter;

void	*thread_routine(void *data)
{
	pthread_t		tid;
	t_counter		*counter;
	unsigned int	i;

	tid = pthread_self();
	// apparently the computer didnt know what the variable is...
	counter = (t_counter *)data;
	pthread_mutex_lock(&counter->count_mutex);
	printf("Thread [%ld]: Count at thread start = %u.\n", tid, counter->count);
	pthread_mutex_unlock(&counter->count_mutex);
	i = 0;
	while (i < TIMES_TO_COUNT)
	{
		pthread_mutex_lock(&counter->count_mutex);
		counter->count++;
		pthread_mutex_unlock(&counter->count_mutex);
		i++;
	}
	pthread_mutex_lock(&counter->count_mutex);
	printf("Final count = %u\n", counter->count);
	pthread_mutex_unlock(&counter->count_mutex);
	return (NULL);
}

int	main(void)
{
	pthread_t	tid1;
	pthread_t	tid2;
	t_counter	counter;

	counter.count = 0;
	pthread_mutex_init(&counter.count_mutex, NULL);
	printf("Expected final count is 42000");
	pthread_create(&tid1, NULL, thread_routine, &counter);
	printf("Main: Created first thread [%ld]\n", tid1);
	pthread_create(&tid2, NULL, thread_routine, &counter);
	printf("Main: Created second thread [%ld]\n", tid2);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	printf("%u \n", counter.count);
	pthread_mutex_destroy(&counter.count_mutex);
	return (0);
}
