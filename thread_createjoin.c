/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 23:28:53 by myakoven          #+#    #+#             */
/*   Updated: 2024/04/28 21:38:49 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdio.h>

// Each thread will count TIMES_TO_COUNT times
#define TIMES_TO_COUNT 21000

#define NC "\e[0m"
#define YELLOW "\e[33m"
#define BYELLOW "\e[1;33m"
#define RED "\e[31m"
#define GREEN "\e[32m"

void	*thread_routine(void *data)
{
	pthread_t		tid;
	unsigned int	i;

	unsigned int *count; 
	tid = pthread_self();
	count = (unsigned int *)data;
	printf("%sThread [%ld]: Count at thread start = %u.%s\n", YELLOW, tid,
		*count, NC);
	i = 0;
	while (i < TIMES_TO_COUNT)
	{
		(*count)++;
		i++;
	}
	printf("%sThread [%ld]: Final count = %u.%s\n", BYELLOW, tid, *count, NC);
	return (NULL); 
}

int	main(void)
{
	pthread_t tid1;
	pthread_t tid2;
	unsigned int count;
	count = 0;
	printf("expected final count is 2000");
	pthread_create(&tid1, NULL, thread_routine, &count);
	printf("%sthread 1 created%s", GREEN, NC);

	pthread_create(&tid2, NULL, thread_routine, &count);
	printf("%sthread 2 created%s", GREEN, NC);
	pthread_join(tid1, NULL);
	printf("Main: Joined first thread [%ld]\n", tid1);
	pthread_join(tid2, NULL);
	printf("Main: Joined second thread [%ld]\n", tid1);
}