/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:43:44 by naharagu          #+#    #+#             */
/*   Updated: 2022/12/28 18:10:42 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

size_t	get_millisecond(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	int			sign;
	long long	res;

	sign = 1;
	res = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (ft_isdigit(*str))
	{
		if (sign == 1 && (res > ((LONG_MAX - (*str - '0')) * sign) / 10))
			return ((int)LONG_MAX);
		else if (sign == -1 && (res < ((LONG_MIN - (*str - '0')) * sign) / 10))
			return ((int)LONG_MIN);
		res = res * 10 + ((*str++ - '0') * sign);
	}
	return (res);
}