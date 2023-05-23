/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:18:04 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/23 21:02:02 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

/*
States:
	1 - thinking: which is idle mode
	2 - eating: active mode
	3 - sleeping: active mode
*/
typedef struct s_philo_config
{
	int				should_eat;
	struct timeval	eat_duration;
	struct timeval	die_duration;
	struct timeval	sleep_duration;
}				t_philo_config;

typedef struct s_forks_lock
{
	int				forks;
	pthread_mutex_t	mutex;
}			t_forks_lock;

typedef struct s_data
{
	t_forks_lock	*forks;
	int				id;
	t_philo_config	*config;
}			t_data;

#endif
