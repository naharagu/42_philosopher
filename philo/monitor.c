/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:38:50 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/13 09:21:08 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

void	*monitor_philo(void *p)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *) p;
	info = philo->info;
	while (true)
	{
		pthread_mutex_lock(&info->control);
		if (info->num_finish_must == info->num_philo)
			info->flag_end = true;
		if ((get_millisecond() - philo->time_last_ate) > info->time_die
			&& !info->flag_end)
		{
			info->time_stamp = get_millisecond();
			print_action(philo, "died");
			info->flag_end = true;
		}
		if (info->flag_end)
		{
			pthread_mutex_unlock(&info->fork[philo->id - 1]);
			pthread_mutex_unlock(&info->control);
			return (NULL);
		}
		pthread_mutex_unlock(&info->control);
	}
}
