/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:38:50 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/03 10:39:14 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

void	monitor_philo(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	while (true)
	{
		if (info->cnt_finish_must == info->num_must_eat)
			info->flag_end = true;
		if ((get_millisecond() - philo->time_last_ate) > info->time_die)
		{
			info->time_stamp = get_millisecond();
			print_action(philo, "died");
			info->flag_end = true;
		}
		if (info->flag_end)
		{
			pthread_mutex_unlock(&info->fork[philo->id - 1]);
			// pthread_mutex_lock(&info->print);
			return ;
		}
	}
}

void	start_monitor(t_philo *philo)
{
	pthread_t	moni;

	pthread_create(&moni, NULL, monitor_philo, philo);
	pthread_join(&moni, NULL);
	return ;
}
