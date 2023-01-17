/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 20:57:03 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/17 20:42:13 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

void	ajust_time(time_t ajust_dutation)
{
	time_t	target_time;

	target_time = get_millisecond() * 1000 + ajust_dutation * 1000;
	while (get_millisecond() * 1000 < target_time)
		usleep(100);
}

void	philo_fork(t_philo *philo)
{
	int	id;
	int	num;

	id = philo->id;
	num = philo->info->num_philo;
	pthread_mutex_lock(&philo->info->fork[id - 1]);
	print_action(philo, "has taken a fork");
	if (num == 1)
		return ;
	if (id != num)
		pthread_mutex_lock(&philo->info->fork[id]);
	else
		pthread_mutex_lock(&philo->info->fork[0]);
	print_action(philo, "has taken a fork");
	return ;
}

void	philo_eat(t_philo *philo)
{
	int	id;
	int	num;

	id = philo->id;
	num = philo->info->num_philo;
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->lock_time_last_ate);
	philo->time_last_start_eating = get_millisecond();
	pthread_mutex_unlock(&philo->lock_time_last_ate);
	ajust_time(philo->info->time_eat);
	pthread_mutex_unlock(&philo->info->fork[id - 1]);
	if (id != num)
		pthread_mutex_unlock(&philo->info->fork[id]);
	else
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
			philo->info->cnt_finish_eating++;
		pthread_mutex_unlock(&philo->info->lock_num_eat);
	}
	print_action(philo, "is sleeping");
	ajust_time(philo->info->time_sleep);
	print_action(philo, "is thinking");
	return ;
}

void	*philo(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	philo->time_last_start_eating = get_millisecond();
	if (philo->id % 2 == 0)
		usleep(500);
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
