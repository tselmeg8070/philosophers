/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:05:34 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/23 21:38:02 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long timeval_to_milliseconds(struct timeval tv) {
    return (long long)tv.tv_sec * 1000LL + (long long)tv.tv_usec / 1000LL;
}

void	*ft_loop_thread(void *arg)
{
	t_data			*data;
	struct timeval	now;
	struct timeval	state_time;
	struct timeval	die_time;
	int				state;

	state = 1;
	data = (t_data *) arg;
	gettimeofday(&now, NULL);
	die_time.tv_usec = now.tv_usec + data->config->die_duration.tv_usec;
	printf("Die time: %ld\n", die_time.tv_usec);
	printf("Now time: %ld\n", now.tv_usec);
	while (1)
	{
		usleep(4000);
		gettimeofday(&now, NULL);
		if (die_time.tv_usec < now.tv_usec)
			break;
	}
	printf("Philo %d: I'm dead\n", data->id);
	return (NULL);
}

int	main(int argc, char **argv)
{
	int				n = 5;
	pthread_t		threads[n];
	t_philo_config	config;
	int				i;
	t_forks_lock	forks;
	struct timeval	now;
	t_data			data[n];

	gettimeofday(&now, NULL);
	config.should_eat = -1;
	config.die_duration.tv_usec = 100000;
	config.eat_duration.tv_usec = 1000;
	config.sleep_duration.tv_usec = 1000;
	forks.forks = n / 2;
	pthread_mutex_init(&forks.mutex, NULL);
	i = 0;
	while (i < n)
	{
		data[i].config = &config;
		data[i].id = i;
		data[i].forks = &forks;
		pthread_create(&threads[i], NULL, ft_loop_thread, &data[i]);
		i++;
	}
	i = 0;
	while (i < n)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	 pthread_mutex_destroy(&forks.mutex);
	return (0);
}
