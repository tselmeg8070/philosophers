/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:05:34 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/29 23:17:29 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_get_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long) tv.tv_sec * 1000LL + (long long) tv.tv_usec / 1000LL);
}

static int	ft_init_thread_data(t_data *data, int n, t_philo_config *config)
{
	int		i;

	i = 0;
	while (i < n)
	{
		memset(&data[i].fork_data.mutex, 0, sizeof(pthread_mutex_t));
		if (pthread_mutex_init(&data[i].fork_data.mutex, NULL) != 0)
			return (0);
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
	return (1);
}

static int	ft_init_config(t_philo_config *config, int argc, char **argv)
{
	if (ft_philo_parse(argc, argv, config))
	{
		config->now = ft_get_now();
		config->ate_lock.stop_flag = 0;
		config->time_lock.now = config->now;
		config->time_lock.n = malloc(sizeof(int) * config->count);
		if (config->time_lock.n == NULL)
			return (0);
		config->ate_lock.ate = malloc(sizeof(int) * config->count);
		if (config->ate_lock.ate == NULL)
		{
			free(config->time_lock.n);
			return (0);
		}
		memset(config->ate_lock.ate, 0, sizeof(int) * config->count);
		memset(config->time_lock.n, 0, sizeof(int) * config->count);
		memset(&config->time_lock.mutex, 0, sizeof(pthread_mutex_t));
		memset(&config->ate_lock.mutex, 0, sizeof(pthread_mutex_t));
		memset(&config->print_lock.mutex, 0, sizeof(pthread_mutex_t));
		pthread_mutex_init(&config->time_lock.mutex, NULL);
		pthread_mutex_init(&config->ate_lock.mutex, NULL);
		pthread_mutex_init(&config->print_lock.mutex, NULL);
		return (1);
	}
	return (0);
}

void	ft_destroyer(pthread_t *threads, t_philo_config *config, t_data *data)
{
	int	i;

	i = -1;
	while (++i < config->count)
		pthread_join(threads[i], NULL);
	ft_philo_free_data(config, data);
	ft_philo_free_config(config);
	free(threads);
}

int	main(int argc, char **argv)
{
	pthread_t		*threads;
	t_philo_config	config;
	t_data			*data;
	int				i;

	if (!ft_init_config(&config, argc, argv))
	{
		write(2, "error\n", 6);
		return (1);
	}
	data = malloc(sizeof(t_data) * config.count);
	if (data == NULL)
		ft_data_err(&config);
	threads = malloc(sizeof(pthread_t) * config.count);
	if (threads == NULL)
		return (ft_thread_err(&config, data));
	if (ft_init_thread_data(data, config.count, &config))
	{
		i = -1;
		while (++i < config.count)
			pthread_create(&threads[i], NULL, ft_loop_thread, &data[i]);
	}
	ft_destroyer(threads, &config, data);
	return (0);
}
