/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:18:24 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/29 22:41:13 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_print_long(long long time)
{
	if (time != 0)
	{
		ft_print_long(time / 10);
		ft_putchar('0' + (time % 10));
	}
}

void	ft_print_int(int time)
{
	if (time != 0)
	{
		ft_print_long(time / 10);
		ft_putchar('0' + (time % 10));
	}
}

void	ft_philo_print(long long time, int id, char *action, t_data *data)
{
	pthread_mutex_lock(&data->config->print_lock.mutex);
	if (time == 0)
		ft_putchar('0');
	ft_print_long(time);
	ft_putchar(' ');
	ft_print_int(id);
	ft_putchar(' ');
	write(1, action, ft_strlen((const unsigned char *) action));
	pthread_mutex_unlock(&data->config->print_lock.mutex);
}
