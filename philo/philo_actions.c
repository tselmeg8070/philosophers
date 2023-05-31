/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:10:12 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/31 18:02:50 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_eat(t_data *data, t_thread_config *config)
{
	pthread_mutex_lock(&data->config->ate_lock.mutex);
	if (data->config->ate_lock.stop_flag == 0)
		ft_philo_print(config->now, data->id, PHILO_FORK, data);
	pthread_mutex_unlock(&data->config->ate_lock.mutex);
	data->fork_data.fork = 0;
	data->fork_data.time = config->now + config->eat_duration;
	data->next->fork_data.fork = 0;
	data->next->fork_data.time = config->now + config->eat_duration;
	config->die_time = config->now + config->die_duration;
	config->state = 2;
	config->state_time = config->now + config->eat_duration;
	pthread_mutex_lock(&data->config->ate_lock.mutex);
	if (data->config->ate_lock.stop_flag == 0)
		ft_philo_print(config->now, data->id, PHILO_EAT, data);
	pthread_mutex_unlock(&data->config->ate_lock.mutex);
}

void	ft_philo_sleep(t_data *data, t_thread_config *config)
{
	data->fork_data.fork = 1;
	data->next->fork_data.fork = 1;
	config->state = 3;
	config->state_time = config->now + config->sleep_duration;
	if (config->should_eat != -1 && config->should_eat != 0)
		config->should_eat--;
	pthread_mutex_lock(&data->config->ate_lock.mutex);
	if (data->config->ate_lock.stop_flag == 0)
		ft_philo_print(config->now, data->id, PHILO_SLEEP, data);
	pthread_mutex_unlock(&data->config->ate_lock.mutex);
}

void	ft_philo_decide(t_data *data, t_thread_config *config)
{
	if (config->state == 3 && config->now == config->state_time)
	{
		if (config->now == data->next->fork_data.time)
			ft_philo_eat(data, config);
		else
		{
			config->state = 1;
			pthread_mutex_lock(&data->config->ate_lock.mutex);
			if (data->config->ate_lock.stop_flag == 0)
				ft_philo_print(config->now, data->id, PHILO_THINK, data);
			pthread_mutex_unlock(&data->config->ate_lock.mutex);
		}
	}
}

int	ft_should_end_check(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->config->count)
	{
		if (data->config->ate_lock.ate[i] == 0)
			return (0);
	}
	return (1);
}

void	ft_philo_die(t_data *data, t_thread_config *config)
{
	if (config->die_time == config->now
		&& pthread_mutex_lock(&data->config->ate_lock.mutex) == 0)
	{
		if (data->config->ate_lock.stop_flag == 0)
		{
			ft_philo_print(config->now, data->id, PHILO_DIE, data);
			data->config->ate_lock.stop_flag = 1;
		}
		pthread_mutex_unlock(&data->config->ate_lock.mutex);
	}
	if (config->should_eat == 0
		&& pthread_mutex_lock(&data->config->ate_lock.mutex) == 0)
	{
		data->config->ate_lock.ate[data->id - 1] = 1;
		if (ft_should_end_check(data))
			data->config->ate_lock.stop_flag = 1;
		pthread_mutex_unlock(&data->config->ate_lock.mutex);
	}
}
