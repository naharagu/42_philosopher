/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:38:50 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/17 20:32:53 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

void	print_died(t_philo *philo)
{
	time_t	time;

	time = get_millisecond() - philo->info->time_start;
	printf("%lu %d %s\n", time, philo->id, "died");
}

int	check_died(t_philo *philo)
{
	time_t	now;

	pthread_mutex_lock(&philo->lock_time_last_ate);
	now = get_millisecond();
	if ((now - philo->time_last_start_eating) > philo->info->time_die)
	{
		pthread_mutex_unlock(&philo->lock_time_last_ate);
		pthread_mutex_lock(&philo->info->lock_end);
		philo->info->end_flag = true;
		pthread_mutex_unlock(&philo->info->lock_end);
		print_died(philo);
		return (1);
	}
	pthread_mutex_unlock(&philo->lock_time_last_ate);
	return (0);
}

void	*monitor_philo(void *p)
{
	int		i;
	t_info	*info;

	info = (t_info *) p;
	while (true)
	{
		pthread_mutex_lock(&info->lock_num_eat);
		if (info->cnt_finish_eating == info->num_philo)
		{
			pthread_mutex_unlock(&info->lock_num_eat);
			pthread_mutex_lock(&info->lock_end);
			info->end_flag = true;
			pthread_mutex_unlock(&info->lock_end);
			return (NULL);
		}
		pthread_mutex_unlock(&info->lock_num_eat);
		i = 0;
		while (i < info->num_philo)
		{
			if (check_died(&info->philo[i]))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
}

int	start_monitor(t_info *info)
{
	pthread_t	thread_moni;

	if (pthread_create(&thread_moni, NULL, monitor_philo, info))
		return (-1);
	pthread_join(thread_moni, NULL);
	return (0);
}
