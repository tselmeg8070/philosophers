/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:05:34 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/24 20:15:01 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_get_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long) tv.tv_sec * 1000LL + (long long) tv.tv_usec / 1000LL);
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
		usleep(1000);
		now += 1;
		if (state == 1 && data != data->next
			&& data->fork_data.fork && data->next->fork_data.fork)
		{
			if (data->fork_data.fork && data->next->fork_data.fork)
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
		else if (state == 2 && now == state_time)
		{
			pthread_mutex_lock(&data->fork_data.mutex);
			pthread_mutex_lock(&data->next->fork_data.mutex);
			data->fork_data.fork = 1;
			data->next->fork_data.fork = 1;
			pthread_mutex_unlock(&data->fork_data.mutex);
			pthread_mutex_unlock(&data->next->fork_data.mutex);
			state = 3;
			state_time = now + data->config->sleep_duration;
			printf("%lld %d %s", now, data->id, PHILO_SLEEP);
		}
		else if (state == 3 && now == state_time)
		{
			if (data->fork_data.fork && data->next->fork_data.fork)
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
		if (die_time < now)
		{
			printf("%lld %d %s", now, data->id, PHILO_DIE);
			data->config->stop_flag = 1;
		}
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
		if (i + 1 < n)
			data[i].next = &data[i + 1];
		else
			data[i].next = &data[0];
		i++;
	}
}

int	main(int argc, char **argv)
{
	int				n = 4;
	pthread_t		threads[n];
	t_philo_config	config;
	t_data			data[n];
	int				i;

	config.die_duration = 600;
	config.eat_duration = 300;
	config.sleep_duration = 300;
	config.should_eat = -1;
	config.now = ft_get_now();
	config.stop_flag = 0;
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
	return (0);
}
