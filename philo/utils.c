/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:43:44 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/14 09:24:57 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

size_t	get_millisecond(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_action(t_philo *philo, char *action)
{
	size_t	time;

	pthread_mutex_lock(&philo->info->lock_end);
	if (philo->info->end_flag)
	{
		pthread_mutex_unlock(&philo->info->lock_end);
		return ;
	}
	pthread_mutex_unlock(&philo->info->lock_end);
	pthread_mutex_lock(&philo->info->lock_time_stamp);
	philo->info->time_stamp = get_millisecond();
	time = philo->info->time_stamp - philo->info->time_start;
	pthread_mutex_unlock(&philo->info->lock_time_stamp);
	// pthread_mutex_lock(&philo->info->print_lock);
	printf("%lu %d %s\n", time, philo->id, action);
	// pthread_mutex_unlock(&philo->info->print_lock);
}

void	free_all(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		pthread_mutex_destroy(&info->fork[i]);
		pthread_mutex_destroy(&info->philo[i].lock_time_last_ate);
		i++;
	}
	pthread_mutex_destroy(&info->lock_end);
	pthread_mutex_destroy(&info->lock_num_eat);
	pthread_mutex_destroy(&info->lock_time_stamp);
	free(info->philo);
	free(info->fork);
	free(info);
	return ;
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
