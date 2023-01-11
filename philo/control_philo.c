/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 20:57:03 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/11 21:50:31 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

void	ajust_time(size_t ajust_dutation)
{
	size_t	target_time;

	target_time = get_millisecond() + ajust_dutation;
	while (get_millisecond() < target_time)
		usleep(100);
}

void	philo_fork(t_philo *philo)
{
	size_t	id;
	size_t	num;

	id = philo->id;
	num = philo->info->num_philo;
	pthread_mutex_lock(&philo->info->fork[id - 1]);
	if (!philo->info->flag_end)
		print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->info->fork[id % num]);
	if (!philo->info->flag_end)
		print_action(philo, "has taken a fork");
	return ;
}

void	philo_eat(t_philo *philo)
{
	size_t	id;
	size_t	num;

	id = philo->id;
	num = philo->info->num_philo;
	if (!philo->info->flag_end)
		print_action(philo, "is eating");
	ajust_time(philo->info->time_eat);
	philo->info->time_stamp = get_millisecond();
	philo->time_last_ate = get_millisecond();
	pthread_mutex_unlock(&philo->info->fork[id - 1]);
	pthread_mutex_unlock(&philo->info->fork[id % num]);
	return ;
}

void	philo_sleep_think(t_philo *philo)
{
	if (philo->info->num_must_eat != -1)
	{
		philo->cnt_times_ate++;
		if (philo->cnt_times_ate == philo->info->num_must_eat)
			philo->info->num_finish_must++;
	}
	if (!philo->info->flag_end)
		print_action(philo, "is sleeping");
	ajust_time(philo->info->time_sleep);
	philo->info->time_stamp = get_millisecond();
	if (!philo->info->flag_end)
		print_action(philo, "is thinking");
	return ;
}

void	*control_philo(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2 == 1)
		ajust_time(100);
	start_monitor(philo);
	while (true)
	{
		philo_fork(philo);
		philo_eat(philo);
		philo_sleep_think(philo);
		pthread_mutex_lock(&philo->info->control);
		if (philo->info->flag_end)
		{
			pthread_mutex_unlock(&philo->info->control);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->info->control);
	}
}
