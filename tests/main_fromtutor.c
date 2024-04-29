/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fromtutor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 23:28:53 by myakoven          #+#    #+#             */
/*   Updated: 2024/04/29 17:09:21 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

#define NC	"\e[0m"
#define YELLOW	"\e[33m"
#define BYELLOW	"\e[1;33m"
#define RED	"\e[31m"
#define GREEN	"\e[32m"

typedef	struct s_locks
{
	pthread_mutex_t	lock_1;
	pthread_mutex_t	lock_2;
	unsigned int	count;
}	t_locks;

// The first thread invokes this routine:
void	*thread_1_routine(void *data)
{
	pthread_t	tid;
	t_locks		*locks;
	
	tid = pthread_self();
	locks = (t_locks *)data;
	printf("%sThread [%ld]: wants lock 1%s\n", YELLOW, tid, NC);
	pthread_mutex_lock(&locks->lock_1);
	printf("%sThread [%ld]: owns lock 1%s\n", BYELLOW, tid, NC);
	printf("%sThread [%ld]: wants lock 2%s\n", YELLOW, tid, NC);
	pthread_mutex_lock(&locks->lock_2);
	printf("%sThread [%ld]: owns lock 2%s\n", BYELLOW, tid, NC);
	locks->count += 1;
	printf("%sThread [%ld]: unlocking lock 2%s\n", BYELLOW, tid, NC);
	pthread_mutex_unlock(&locks->lock_2);
	printf("%sThread [%ld]: unlocking lock 1%s\n", BYELLOW, tid, NC);
	pthread_mutex_unlock(&locks->lock_1);
	printf("%sThread [%ld]: finished%s\n", YELLOW, tid, NC);
	return (NULL); // The thread ends here.
}

// The second thread invokes this routine:
void	*thread_2_routine(void *data)
{
	pthread_t	tid;
	t_locks		*locks;
	
	tid = pthread_self();
	locks = (t_locks *)data;
	printf("%sThread [%ld]: wants lock 2%s\n", YELLOW, tid, NC);
	pthread_mutex_lock(&locks->lock_2);
	printf("%sThread [%ld]: owns lock 2%s\n", BYELLOW, tid, NC);
	printf("%sThread [%ld]: wants lock 1%s\n", YELLOW, tid, NC);
	pthread_mutex_lock(&locks->lock_1);
	printf("%sThread [%ld]: owns lock 1%s\n", BYELLOW, tid, NC);
	locks->count += 1;
	printf("%sThread [%ld]: unlocking lock 1%s\n", BYELLOW, tid, NC);
	pthread_mutex_unlock(&locks->lock_1);
	printf("%sThread [%ld]: unlocking lock 2%s\n", BYELLOW, tid, NC);
	pthread_mutex_unlock(&locks->lock_2);
	printf("%sThread [%ld]: finished.%s\n", YELLOW, tid, NC);
	return (NULL); // The thread ends here.
}

int	main(void)
{
	pthread_t	tid1;	// ID of the first thread
	pthread_t	tid2;	// ID of the second thread
	t_locks		locks;	// Structure containing 2 mutexes

	locks.count = 0;
	// Initialize both mutexes :
	pthread_mutex_init(&locks.lock_1, NULL);
	pthread_mutex_init(&locks.lock_2, NULL);
	// Thread creation:
	pthread_create(&tid1, NULL, thread_1_routine, &locks);
	printf("Main: Created first thread [%ld]\n", tid1);
	pthread_create(&tid2, NULL, thread_2_routine, &locks);
	printf("Main: Created second thread [%ld]\n", tid2);
	// Thread joining:
	pthread_join(tid1, NULL);
	printf("Main: Joined first thread [%ld]\n", tid1);
	pthread_join(tid2, NULL);
	printf("Main: Joined second thread [%ld]\n", tid2);
	// Final count evaluation:
	if (locks.count == 2)
		printf("%sMain: OK. Total count is %d\n", GREEN, locks.count);
	else
		printf("%sMain: ERROR ! Total count is %u\n", RED, locks.count);
	// Mutex destruction:
	pthread_mutex_destroy(&locks.lock_1);
	pthread_mutex_destroy(&locks.lock_2);
	return (0);
}


/*
#include <stdio.h>
#include <pthread.h>

// Each thread will count TIMES_TO_COUNT times
#define TIMES_TO_COUNT 21000

#define NC	"\e[0m"
#define YELLOW	"\e[33m"
#define BYELLOW	"\e[1;33m"
#define RED	"\e[31m"
#define GREEN	"\e[32m"

// This structure contains the count as well as the mutex
// that will protect the access to the variable.
typedef	struct s_counter
{
	pthread_mutex_t	count_mutex;
	unsigned int	count;
} t_counter;

void	*thread_routine(void *data)
{
	// Each thread starts here
	pthread_t	tid;
	t_counter	*counter; // pointer to the structure in main
	unsigned int	i;

	tid = pthread_self();
	counter = (t_counter *)data;
	// Print the count before this thread starts iterating.
	// In order to read the value of count, we lock the mutex:
	pthread_mutex_lock(&counter->count_mutex);
	printf("%sThread [%ld]: Count at thread start = %u.%s\n",
		YELLOW, tid, counter->count, NC);
	pthread_mutex_unlock(&counter->count_mutex);
	i = 0;
	while (i < TIMES_TO_COUNT)
	{
		// Iterate TIMES_TO_COUNT times
		// Increment the counter at each iteration
		// Lock the mutex for the duration of the incrementation
		pthread_mutex_lock(&counter->count_mutex);
		counter->count++;
		pthread_mutex_unlock(&counter->count_mutex);
		i++;
	}
	// Print the final count when this thread finishes its
	// own count, without forgetting to lock the mutex:
	pthread_mutex_lock(&counter->count_mutex);
	printf("%sThread [%ld]: Final count = %u.%s\n",
		BYELLOW, tid, counter->count, NC);
	pthread_mutex_unlock(&counter->count_mutex);
	return (NULL); // Thread termine ici.
}

int	main(void)
{
	pthread_t	tid1;
	pthread_t	tid2;
	// Structure containing the threads' total count:
	t_counter	counter;

	// There is only on thread here (main thread), so we can safely
	// initialize count without using the mutex.
	counter.count = 0;
	// Initialize the mutex :
	pthread_mutex_init(&counter.count_mutex, NULL);
	// Since each thread counts TIMES_TO_COUNT times and that
	// we have 2 threads, we expect the final count to be
	// 2 * TIMES_TO_COUNT:
	printf("Main: Expected count is %s%u%s\n", GREEN, 
					2 * TIMES_TO_COUNT, NC);
	// Thread creation:
	pthread_create(&tid1, NULL, thread_routine, &counter);
	printf("Main: Created first thread [%ld]\n", tid1);
	pthread_create(&tid2, NULL, thread_routine, &counter);
	printf("Main: Created second thread [%ld]\n", tid2);
	// Thread joining:
	pthread_join(tid1, NULL);
	printf("Main: Joined first thread [%ld]\n", tid1);
	pthread_join(tid2, NULL);
	printf("Main: Joined second thread [%ld]\n", tid2);
	// Final count evaluation:
	// (Here we can read the count without worrying about
	// the mutex because all threads have been joined and
	// there can be no data race between threads)
	if (counter.count != (2 * TIMES_TO_COUNT))
		printf("%sMain: ERROR ! Total count is %u%s\n",
					RED, counter.count, NC);
	else
		printf("%sMain: OK. Total count is %u%s\n",
					GREEN, counter.count, NC);
	// Destroy the mutex at the end of the program:
	pthread_mutex_destroy(&counter.count_mutex);
	return (0);
}
*/
