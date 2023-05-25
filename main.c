/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:05:34 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/25 20:27:42 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_get_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long) tv.tv_sec * 1000LL + (long long) tv.tv_usec / 1000LL);
}

int		ft_check_time_lock(int *arr, int n)
{
	while (--n >= 0)
	{
		if (arr[n] == 0)
			return (0);
	}
	return (1);
}

void	*ft_loop_thread(void *arg)
{
	t_data		*data;
	long long	state_time;
	long long	die_time;
	long long	now;
	int			should_eat;
	int			state;

	state = 1;
	data = (t_data *) arg;
	now = data->config->now;
	should_eat = data->config->should_eat;
	die_time = now + data->config->die_duration;
	state_time = now;
	while (!data->config->stop_flag)
	{
		if (data->config->time_lock.now == now)
		{
			data->config->time_lock.n[data->id - 1] = 1;
			if (ft_check_time_lock(data->config->time_lock.n, data->config->count))
			{
				pthread_mutex_lock(&data->config->time_lock.mutex);
				memset(data->config->time_lock.n, 0, sizeof(int) * data->config->count);
				data->config->time_lock.now++;
				pthread_mutex_unlock(&data->config->time_lock.mutex);
			}
		}
		else
		{
			if (state == 1 && data != data->next
				&& data->fork_data.fork && data->next->fork_data.fork)
			{
				if (data->config->now == now && data->id % 2 == 1
					&& (data->id != data->config->count))
				{
					pthread_mutex_lock(&data->fork_data.mutex);
					pthread_mutex_lock(&data->next->fork_data.mutex);
					data->fork_data.fork = 0;
					data->next->fork_data.fork = 0;
					pthread_mutex_unlock(&data->fork_data.mutex);
					pthread_mutex_unlock(&data->next->fork_data.mutex);
					die_time = now + data->config->die_duration;
					state = 2;
					state_time = now + data->config->eat_duration;
					should_eat--;
					printf("%lld %d %s", now, data->id, PHILO_EAT);
				}
				else if (data->config->now != now && data->fork_data.fork && data->next->fork_data.fork
					&& now == data->next->fork_data.time)
				{
					pthread_mutex_lock(&data->fork_data.mutex);
					pthread_mutex_lock(&data->next->fork_data.mutex);
					data->fork_data.fork = 0;
					data->next->fork_data.fork = 0;
					pthread_mutex_unlock(&data->fork_data.mutex);
					pthread_mutex_unlock(&data->next->fork_data.mutex);
					die_time = now + data->config->die_duration;
					state = 2;
					state_time = now + data->config->eat_duration;
					should_eat--;
					printf("%lld %d %s", now, data->id, PHILO_EAT);
				}
			}
			else if (state == 2 && now + 3 == state_time)
			{
				pthread_mutex_lock(&data->fork_data.mutex);
				pthread_mutex_lock(&data->next->fork_data.mutex);
				data->fork_data.fork = 1;
				data->next->fork_data.fork = 1;
				data->fork_data.time = now + 3;
				data->next->fork_data.time = now + 3;
				pthread_mutex_unlock(&data->fork_data.mutex);
				pthread_mutex_unlock(&data->next->fork_data.mutex);
				state = 3;
				state_time = now + 3 + data->config->sleep_duration;
				printf("%lld %d %s", now + 3, data->id, PHILO_SLEEP);
			}
			else if (state == 3 && now == state_time)
			{
				if (data->fork_data.fork && data->next->fork_data.fork
					&& now == data->fork_data.time && now == data->next->fork_data.time)
				{
					pthread_mutex_lock(&data->fork_data.mutex);
					pthread_mutex_lock(&data->next->fork_data.mutex);
					data->fork_data.fork = 0;
					data->next->fork_data.fork = 0;
					pthread_mutex_unlock(&data->fork_data.mutex);
					pthread_mutex_unlock(&data->next->fork_data.mutex);
					die_time = now + data->config->die_duration;
					state = 2;
					state_time = now + data->config->eat_duration;
					should_eat--;
					printf("%lld %d %s", now, data->id, PHILO_EAT);
				}
				else
				{
					state = 1;
					printf("%lld %d %s", now, data->id, PHILO_THINK);
				}
			}
			if (should_eat != -1 && should_eat == 0)
				data->config->stop_flag = 1;
			if (die_time == now)
			{
				printf("%lld %d %s", now, data->id, PHILO_DIE);
				data->config->stop_flag = 1;
			}
			now += 1;
		}
		usleep(1000);
	}
	return (NULL);
}

void	ft_init_thread_data(t_data *data, int n, t_philo_config *config)
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

int	ft_init_config(t_philo_config *config, int n)
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
