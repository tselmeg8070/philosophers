/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:11:27 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/26 18:55:41 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_time_lock(int *arr, int n)
{
	while (--n >= 0)
	{
		if (arr[n] == 0)
			return (0);
	}
	return (1);
}

static void	ft_init_loop(t_thread_config *config, t_data *data)
{
	config->state = 1;
	config->now = data->config->now;
	config->should_eat = data->config->should_eat;
	config->die_time = config->now + data->config->die_duration;
	config->state_time = config->now;
}

static int	ft_time_lock(t_data *data, t_thread_config *config)
{
	t_philo_config	*gconf;

	gconf = data->config;
	pthread_mutex_lock(&gconf->time_lock.mutex);
	if (gconf->time_lock.now == config->now)
	{
		gconf->time_lock.n[data->id - 1] = 1;
		if (ft_check_time_lock(gconf->time_lock.n, gconf->count))
		{
			memset(gconf->time_lock.n, 0, sizeof(int) * gconf->count);
			gconf->time_lock.now++;
		}
		pthread_mutex_unlock(&gconf->time_lock.mutex);
		return (0);
	}
	pthread_mutex_unlock(&gconf->time_lock.mutex);
	return (1);
}

void	*ft_loop_thread(void *arg)
{
	t_data			*data;
	t_thread_config	config;

	data = (t_data *)arg;
	ft_init_loop(&config, data);
	while (!data->config->stop_flag)
	{
		if (ft_time_lock(data, &config))
		{
			pthread_mutex_lock(&data->fork_data.mutex);
			pthread_mutex_lock(&data->next->fork_data.mutex);
			if (ft_eat_condition(data, &config))
				ft_philo_eat(data, &config);
			else if (ft_sleep_condition(&config))
				ft_philo_sleep(data, &config);
			else
				ft_philo_decide(data, &config);
			pthread_mutex_unlock(&data->fork_data.mutex);
			pthread_mutex_unlock(&data->next->fork_data.mutex);
			ft_philo_die(data, &config);
			config.now += 1;
		}
		usleep(1000);
	}
	return (NULL);
}
