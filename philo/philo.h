/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:18:04 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/29 23:17:16 by tadiyamu         ###   ########.fr       */
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

# define PHILO_FORK " has taken a fork\n"
# define PHILO_EAT " is eating\n"
# define PHILO_SLEEP " is sleeping\n"
# define PHILO_THINK " is thinking\n"
# define PHILO_DIE " died\n"

typedef struct s_time_lock
{
	long long		now;
	int				*n;
	pthread_mutex_t	mutex;
}			t_time_lock;

typedef struct s_ate_lock
{
	int				*ate;
	int				stop_flag;
	pthread_mutex_t	mutex;
}			t_ate_lock;

typedef struct s_print_lock
{
	pthread_mutex_t	mutex;
}	t_print_lock;

/*
States:
	1 - thinking: which is idle mode
	2 - eating: active mode
	3 - sleeping: active mode
*/
typedef struct s_philo_config
{
	int				should_eat;
	int				count;
	long long		eat_duration;
	long long		die_duration;
	long long		sleep_duration;
	long long		now;
	t_time_lock		time_lock;
	t_ate_lock		ate_lock;
	t_print_lock	print_lock;
}				t_philo_config;

typedef struct s_thread_config
{
	long long	state_time;
	long long	die_time;
	long long	now;
	long long	eat_duration;
	long long	die_duration;
	long long	sleep_duration;
	int			should_eat;
	int			state;
}				t_thread_config;

typedef struct s_forks_lock
{
	int				fork;
	long long		time;
	pthread_mutex_t	mutex;
}			t_forks_lock;

typedef struct s_data
{
	t_forks_lock	fork_data;
	int				id;
	t_philo_config	*config;
	struct s_data	*next;
}			t_data;

size_t		ft_strlen(const unsigned char *str);

void		ft_philo_print(long long time, int id, char *action, t_data *data);

void		*ft_loop_thread(void *arg);

int			ft_eat_condition(t_data *data, t_thread_config *config);

int			ft_sleep_condition(t_thread_config *config);

void		ft_philo_eat(t_data *data, t_thread_config *config);

void		ft_philo_sleep(t_data *data, t_thread_config *config);

void		ft_philo_decide(t_data *data, t_thread_config *config);

void		ft_philo_die(t_data *data, t_thread_config *config);

int			ft_check_val(char *str, long long val);

long long	ft_atoi(char *str);

int			ft_philo_parse(int argc, char **argv, t_philo_config *config);

long long	ft_get_now(void);

void		ft_philo_free_config(t_philo_config *config);

void		ft_philo_free_data(t_philo_config *config, t_data *data);

int			ft_thread_err(t_philo_config *config, t_data *data);

int			ft_data_err(t_philo_config *config);

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
