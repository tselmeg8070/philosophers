/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 22:59:57 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/29 23:17:56 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_free_config(t_philo_config *config)
{
	pthread_mutex_destroy(&config->time_lock.mutex);
	pthread_mutex_destroy(&config->ate_lock.mutex);
	pthread_mutex_destroy(&config->print_lock.mutex);
	free(config->ate_lock.ate);
	free(config->time_lock.n);
}

void	ft_philo_free_data(t_philo_config *config, t_data *data)
{
	int	i;

	i = -1;
	while (++i < config->count)
		pthread_mutex_destroy(&data[i].fork_data.mutex);
	free(data);
}

int	ft_thread_err(t_philo_config *config, t_data *data)
{
	write(2, "error\n", 6);
	ft_philo_free_data(config, data);
	ft_philo_free_config(config);
	return (1);
}

int	ft_data_err(t_philo_config *config)
{
	write(2, "error\n", 6);
	ft_philo_free_config(config);
	return (1);
}
