/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:29:53 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/30 17:26:45 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi_loop(long long *vals, int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		vals[i - 1] = ft_atoi(argv[i]);
		if (vals[i - 1] <= 0 || !ft_check_val(argv[i], vals[i - 1]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_philo_parse(int argc, char **argv, t_philo_config *config)
{
	long long	vals[5];

	memset(vals, 0, sizeof(long long) * 5);
	if (argc == 5 || argc == 6)
	{
		if (ft_atoi_loop(vals, argc, argv))
		{
			config->count = vals[0];
			config->die_duration = vals[1];
			config->eat_duration = vals[2];
			config->sleep_duration = vals[3];
			if (argc == 6)
				config->should_eat = vals[4];
			else
				config->should_eat = -1;
			return (1);
		}
	}
	return (0);
}
