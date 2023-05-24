/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:18:04 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/24 20:48:01 by tadiyamu         ###   ########.fr       */
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

/*
# 5 800 200 200
# no one should die
# 5 600 150 150
# no one should die
# 4 410 200 200
# no one should die
# 100 800 200 200
# no one should die
# 105 800 200 200
# no one should die
# 200 800 200 200
# no one should die

# 1 800 200 200
# a philo should die
# 4 310 200 100
# a philo should die
# 4 200 205 200
# a philo should die
# 5 800 200 200 7
# no one should die, simulation should stop after 7 eats
# 4 410 200 200 10
# no one should die, simulation should stop after 10 eats
# -5 600 200 200
# should error and not run (no crashing)
# 4 -5 200 200
# should error and not run (no crashing)
# 4 600 -5 200
# should error and not run (no crashing)
# 4 600 200 -5
# should error and not run (no crashing)
# 4 600 200 200 -5
# should error and not run (no crashing)
*/
