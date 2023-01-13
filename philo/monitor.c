/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:38:50 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/13 10:59:45 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

void	print_died(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->info->time_lock);
	philo->info->time_stamp = get_millisecond();
	pthread_mutex_unlock(&philo->info->time_lock);
	pthread_mutex_lock(&philo->info->print_lock);
	time = philo->info->time_stamp - philo->info->time_start;
	printf("%lu %d %s\n", time, philo->id, "died");
	pthread_mutex_unlock(&philo->info->print_lock);
}

void	*monitor_philo(void *p)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *) p;
	info = philo->info;
	while (true)
	{
		pthread_mutex_lock(&info->control_lock);
		if (info->num_finish_must == info->num_philo)
		{
			info->flag_end = true;
			pthread_mutex_unlock(&info->control_lock);
			return (NULL);
		}
		if ((get_millisecond() - philo->time_last_ate) > info->time_die
			&& !info->flag_end)
		{
			print_died(philo);
			info->flag_end = true;
			pthread_mutex_unlock(&info->control_lock);
			pthread_mutex_unlock(&info->fork[philo->id - 1]);
			return (NULL);
		}
		pthread_mutex_unlock(&info->control_lock);
	}
}
