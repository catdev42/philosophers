/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:00:35 by myakoven          #+#    #+#             */
/*   Updated: 2024/05/01 20:35:51 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <pthread.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mutex;
typedef struct s_table	t_table;

/*FORK*/
typedef struct s_fork
{
	t_mutex				fork;
	int					fork_id;
}						t_fork;

// ./philo 5 800 200 200 [5]

typedef struct s_philo
{
	int					id;
	int					meal_count;
	bool				full;
	long				last_mean_time;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_t			thread_id;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	long				philo_num;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long num_limit_meals; //[5] if its -1 then there is no variable
	long				start_simulation;
	bool end_simulation; // a philo dies or all philos are done max meals
	t_fork *forks;       // has mutex fork
	t_philo *philos;     // has pointer to forks

}						t_table;

# define ERROR_MESSAGE "Error Message"

/***UTILS.C***/
void					error_exit(const char *error);

/***LIB.C***/
void					ft_putstr_fd(char *s, int fd);
long					ft_atol(const char *nptr);
void					*ft_calloc(size_t nmemb, size_t size);

#endif