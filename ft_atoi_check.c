/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:40:40 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/26 17:12:38 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(unsigned char *s1, unsigned char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2 && i < n - 1)
	{
		s1++;
		s2++;
		i++;
	}
	return (*s1 - *s2);
}

size_t	ft_strlen(const unsigned char *str)
{
	size_t	c;

	c = 0;
	while (str && str[c] != '\0')
		c++;
	return (c);
}

int	ft_check_val(char *str, long long val)
{
	int	dig;

	dig = 0;
	if (val < 0)
		dig++;
	if (val == 0
		&& ft_strncmp((unsigned char*) str, (unsigned char*) "0", 1) != 0)
		return (0);
	if (val == 0)
		dig = 1;
	while (val != 0)
	{
		dig++;
		val /= 10;
	}
	if (dig == (int) ft_strlen((unsigned char *) str))
		return (1);
	return (0);
}
