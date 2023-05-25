/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:05:34 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/25 21:19:02 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long long	ft_get_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long) tv.tv_sec * 1000LL + (long long) tv.tv_usec / 1000LL);
}

static void	ft_init_thread_data(t_data *data, int n, t_philo_config *config)
{
	int		i;

	i = 0;
	while (i < n)
	{
		memset(&data[i].fork_data.mutex, 0, sizeof(pthread_mutex_t));
		pthread_mutex_init(&data[i].fork_data.mutex, NULL);
		data[i].config = config;
		data[i].id = i + 1;
		data[i].fork_data.fork = 1;
		data[i].fork_data.time = config->now;
		if (i + 1 < n)
			data[i].next = &data[i + 1];
		else
			data[i].next = &data[0];
		i++;
	}
}

static int	ft_init_config(t_philo_config *config, int n)
{
	config->die_duration = 900;
	config->eat_duration = 300;
	config->sleep_duration = 300;
	config->should_eat = -1;
	config->count = n;
	config->now = ft_get_now();
	config->stop_flag = 0;
	config->time_lock.now = config->now;
	config->time_lock.n = malloc(sizeof(int) * n);
	if (config->time_lock.n == NULL)
		return (0);
	memset(config->time_lock.n, 0, sizeof(int) * n);
	memset(&config->time_lock.mutex, 0, sizeof(pthread_mutex_t));
	pthread_mutex_init(&config->time_lock.mutex, NULL);
	return (1);
}

int	main(int argc, char **argv)
{
	int				n = 5;
	pthread_t		threads[n];
	t_philo_config	config;
	t_data			data[n];
	int				i;

	if (!ft_init_config(&config, n))
	{
		write(2, "Memory error\n", 13);
		return (1);
	}
	ft_init_thread_data(data, n, &config);
	i = -1;
	while (++i < n)
		pthread_create(&threads[i], NULL, ft_loop_thread, &data[i]);
	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&data[i].fork_data.mutex);
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&config.time_lock.mutex);
	return (0);
}
