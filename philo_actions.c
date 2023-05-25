/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:10:12 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/25 21:19:36 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_eat(t_data *data, t_thread_config *config)
{
	pthread_mutex_lock(&data->fork_data.mutex);
	pthread_mutex_lock(&data->next->fork_data.mutex);
	data->fork_data.fork = 0;
	data->next->fork_data.fork = 0;
	pthread_mutex_unlock(&data->fork_data.mutex);
	pthread_mutex_unlock(&data->next->fork_data.mutex);
	config->die_time = config->now + data->config->die_duration;
	config->state = 2;
	config->state_time = config->now + data->config->eat_duration;
	config->should_eat--;
	printf("%lld %d %s", config->now, data->id, PHILO_EAT);
}

void	ft_philo_sleep(t_data *data, t_thread_config *config)
{
	pthread_mutex_lock(&data->fork_data.mutex);
	pthread_mutex_lock(&data->next->fork_data.mutex);
	data->fork_data.fork = 1;
	data->next->fork_data.fork = 1;
	data->fork_data.time = config->now + 3;
	data->next->fork_data.time = config->now + 3;
	pthread_mutex_unlock(&data->fork_data.mutex);
	pthread_mutex_unlock(&data->next->fork_data.mutex);
	config->state = 3;
	config->state_time = config->now + 3 + data->config->sleep_duration;
	printf("%lld %d %s", config->now + 3, data->id, PHILO_SLEEP);
}

void	ft_philo_decide(t_data *data, t_thread_config *config)
{
	if (config->state == 3 && config->now == config->state_time)
	{
		if (data->fork_data.fork && data->next->fork_data.fork
			&& config->now == data->fork_data.time
			&& config->now == data->next->fork_data.time)
			ft_philo_eat(data, config);
		else
		{
			config->state = 1;
			printf("%lld %d %s", config->now, data->id, PHILO_THINK);
		}
	}
}

void	ft_philo_die(t_data *data, t_thread_config *config)
{
	if (config->die_time == config->now)
	{
		printf("%lld %d %s", config->now, data->id, PHILO_DIE);
		data->config->stop_flag = 1;
	}
}
