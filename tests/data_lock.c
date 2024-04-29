/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:15:28 by myakoven          #+#    #+#             */
/*   Updated: 2024/04/29 18:16:23 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdio.h>

typedef struct s_locks
{
	pthread_mutex_t	lock_1;
	pthread_mutex_t	lock_2;
	unsigned int	count;
}					t_locks;

void	*thread_1_routine(void *data)
{
	pthread_t	tid;
	t_locks		*locks;

	tid = pthread_self();
	locks = (t_locks *)data;
	printf("Thread [%ld]: wants lock 1\n", tid);
	pthread_mutex_lock(&locks->lock_1);
	printf("Thread [%ld]: owns lock 1\n", tid);
	printf("Thread [%ld]: wants lock 2\n", tid);
	pthread_mutex_lock(&locks->lock_2);
	printf("Thread [%ld]: owns lock 2\n", tid);
	locks->count += 1;
	printf("Thread [%ld]: unlocking lock 2\n", tid);
	pthread_mutex_unlock(&locks->lock_2);
	printf("Thread [%ld]: unlocking lock 1\n", tid);
	pthread_mutex_unlock(&locks->lock_1);
	printf("Thread [%ld]: finished\n", tid);
	return (NULL); // The thread ends here.
}

// The second thread invokes this routine:
void	*thread_2_routine(void *data)
{
	pthread_t	tid;
	t_locks		*locks;

	tid = pthread_self();
	locks = (t_locks *)data;
    printf("Thread [%ld]: wants lock 1\n", tid);
	pthread_mutex_lock(&locks->lock_1);
	printf("Thread [%ld]: owns lock 1\n", tid);
	printf("Thread [%ld]: wants lock 2\n", tid);
	pthread_mutex_lock(&locks->lock_2);
	printf("Thread [%ld]: owns lock 2\n", tid);
	
	locks->count += 1;
	printf("Thread [%ld]: unlocking lock 1\n", tid);
	pthread_mutex_unlock(&locks->lock_1);
	printf("Thread [%ld]: unlocking lock 2\n", tid);
	pthread_mutex_unlock(&locks->lock_2);
	printf("Thread [%ld]: finished.\n", tid);
	return (NULL); // The thread ends here.
}

int	main(void)
{
	t_locks data;
	pthread_t tid1;
	pthread_t tid2;

	data.count = 0;
	pthread_mutex_init(&data.lock_1, NULL);
	pthread_mutex_init(&data.lock_2, NULL);

	pthread_create(&tid1, NULL, thread_1_routine, &data);
	pthread_create(&tid2, NULL, thread_2_routine, &data);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	if (data.count == 2)
		printf("Main: OK. Total count is %d\n", data.count);
	else
		printf("Main: ERROR ! Total count is %u\n", data.count);
	pthread_mutex_destroy(&data.lock_1);
	pthread_mutex_destroy(&data.lock_2);
	return (0);
}