/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop_conditions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:14:11 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/30 18:12:32 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat_condition(t_data *data, t_thread_config *config)
{
	if (config->state == 1 && data != data->next)
	{
		if (data->config->now == config->now && data->id % 2 == 1
			&& (data->id != data->config->count))
			return (1);
		else if (data->config->now != config->now
			&& config->now == data->next->fork_data.time)
			return (1);
	}
	return (0);
}

int	ft_sleep_condition(t_thread_config *config)
{
	if (config->state == 2 && config->now == config->state_time)
		return (1);
	return (0);
}
