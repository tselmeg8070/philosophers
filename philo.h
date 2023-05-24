/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:18:04 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/24 19:09:33 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

# define PHILO_FORK " has taken fork\n"
# define PHILO_EAT " is eating\n"
# define PHILO_SLEEP " is sleeping\n"
# define PHILO_THINK " is thinking\n"
# define PHILO_DIE " died\n"

/*
States:
	1 - thinking: which is idle mode
	2 - eating: active mode
	3 - sleeping: active mode
*/
typedef struct s_philo_config
{
	int			stop_flag;
	int			should_eat;
	long long	eat_duration;
	long long	die_duration;
	long long	sleep_duration;
	long long	now;
}				t_philo_config;

typedef struct s_forks_lock
{
	int				fork;
	pthread_mutex_t	mutex;
}			t_forks_lock;

typedef struct s_data
{
	t_forks_lock	fork_data;
	int				id;
	t_philo_config	*config;
	struct s_data	*next;
}			t_data;

#endif
