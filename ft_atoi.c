/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tadiyamu <tadiyamu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:22:24 by tadiyamu          #+#    #+#             */
/*   Updated: 2023/05/26 14:59:24 by tadiyamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char	*strip_space(char *str)
{
	while (*str == ' ' || (*str >= 9 && *str <= 16))
		str++;
	return (str);
}

static long long	ft_int(int val, int sign_count)
{
	if (sign_count % 2 == 1)
		return (val * (-1));
	return (val);
}

long long	ft_atoi(char *str)
{
	int			count_sign;
	long long	val;

	count_sign = 0;
	val = 0;
	str = strip_space(str);
	if (*str == '+' || *str == '-')
	{
		count_sign = *str == '-';
		str++;
	}
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
			val = val * 10 + (*str - '0');
		else
			return (ft_int(val, count_sign));
		str++;
	}
	return (ft_int(val, count_sign));
}
