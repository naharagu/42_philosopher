/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 20:57:03 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/14 13:22:49 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

void	ajust_time(size_t ajust_dutation)
{
	size_t	target_time;

	target_time = get_millisecond() + ajust_dutation;
	while (get_millisecond() < target_time)
		usleep(10);
}

void	philo_fork(t_philo *philo)
{
	size_t	id;
	size_t	num;

	id = philo->id;
	num = philo->info->num_philo;
	pthread_mutex_lock(&philo->info->fork[id - 1]);
	print_action(philo, "has taken a fork");
	if (num == 1)
		return ;
	if (id != num)
		pthread_mutex_lock(&philo->info->fork[id]);
	else if (id == num)
		pthread_mutex_lock(&philo->info->fork[0]);
	print_action(philo, "has taken a fork");
	return ;
}

void	philo_eat(t_philo *philo)
{
	size_t	id;
	size_t	num;

	id = philo->id;
	num = philo->info->num_philo;
	print_action(philo, "is eating");
	ajust_time(philo->info->time_eat);
	pthread_mutex_lock(&philo->info->lock_time_stamp);
	philo->info->time_stamp = get_millisecond();
	pthread_mutex_unlock(&philo->info->lock_time_stamp);
	pthread_mutex_lock(&philo->lock_time_last_ate);
	philo->time_last_ate = get_millisecond();
	pthread_mutex_unlock(&philo->lock_time_last_ate);
	pthread_mutex_unlock(&philo->info->fork[id - 1]);
	if (id != num)
		pthread_mutex_unlock(&philo->info->fork[id]);
	else if (id == num)
		pthread_mutex_unlock(&philo->info->fork[0]);
	return ;
}

void	philo_sleep_think(t_philo *philo)
{
	if (philo->info->num_must_eat != -1)
	{
		pthread_mutex_lock(&philo->info->lock_num_eat);
		philo->cnt_times_ate++;
		if (philo->cnt_times_ate == philo->info->num_must_eat)
			philo->info->num_finish_must++;
		pthread_mutex_unlock(&philo->info->lock_num_eat);
	}
	print_action(philo, "is sleeping");
	ajust_time(philo->info->time_sleep);
	pthread_mutex_lock(&philo->info->lock_time_stamp);
	philo->info->time_stamp = get_millisecond();
	pthread_mutex_unlock(&philo->info->lock_time_stamp);
	print_action(philo, "is thinking");
	return ;
}

void	*philo(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2 == 1)
		ajust_time(200);
	while (true)
	{
		philo_fork(philo);
		if (philo->info->num_philo == 1)
			return (NULL);
		philo_eat(philo);
		philo_sleep_think(philo);
		pthread_mutex_lock(&philo->info->lock_end);
		if (philo->info->end_flag)
		{
			pthread_mutex_unlock(&philo->info->lock_end);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->info->lock_end);
	}
}
