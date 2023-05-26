/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop_conditions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:14:11 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/26 15:06:29 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat_condition(t_data *data, t_thread_config *config)
{
	if (config->state == 1 && data != data->next && data->fork_data.fork
		&& data->next->fork_data.fork)
	{
		if (data->config->now == config->now && data->id % 2 == 1
			&& (data->id != data->config->count))
			return (1);
		else if (data->config->now != config->now && data->fork_data.fork
			&& data->next->fork_data.fork
			&& config->now == data->next->fork_data.time)
			return (1);
	}
	return (0);
}

int	ft_sleep_condition(t_thread_config *config)
{
	if (config->state == 2 && config->now + 3 == config->state_time)
		return (1);
	return (0);
}
