/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:10:12 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/29 21:34:10 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_eat(t_data *data, t_thread_config *config)
{
	ft_philo_print(config->now, data->id, PHILO_FORK, data);
	data->fork_data.fork = 0;
	data->fork_data.time = config->now + config->eat_duration;
	data->next->fork_data.fork = 0;
	data->next->fork_data.time = config->now + config->eat_duration;
	config->die_time = config->now + config->die_duration;
	config->state = 2;
	config->state_time = config->now + config->eat_duration;
	ft_philo_print(config->now, data->id, PHILO_EAT, data);
}

void	ft_philo_sleep(t_data *data, t_thread_config *config)
{
	data->fork_data.fork = 1;
	data->next->fork_data.fork = 1;
	config->state = 3;
	config->state_time = config->now + config->sleep_duration;
	if (config->should_eat != -1 && config->should_eat != 0)
		config->should_eat--;
	ft_philo_print(config->now, data->id, PHILO_SLEEP, data);
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
			ft_philo_print(config->now, data->id, PHILO_THINK, data);
		}
	}
}

void	ft_philo_die(t_data *data, t_thread_config *config)
{
	int	i;
	int	f;

	if (config->die_time == config->now
		&& pthread_mutex_lock(&data->config->ate_lock.mutex) == 0)
	{
		ft_philo_print(config->now, data->id, PHILO_DIE, data);
		data->config->ate_lock.stop_flag = 1;
		pthread_mutex_unlock(&data->config->ate_lock.mutex);
	}
	if (config->should_eat == 0
		&& pthread_mutex_lock(&data->config->ate_lock.mutex) == 0)
	{
		data->config->ate_lock.ate[data->id - 1] = 1;
		i = -1;
		f = 0;
		while (++i < data->config->count)
		{
			if (data->config->ate_lock.ate[i] == 0)
				f = 1;
		}
		if (f == 0)
			data->config->ate_lock.stop_flag = 1;
		pthread_mutex_unlock(&data->config->ate_lock.mutex);
	}
}
