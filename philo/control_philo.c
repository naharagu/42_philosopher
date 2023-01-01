/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 20:57:03 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/01 23:01:11 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

void	take_forks(t_philo *philo)
{
	size_t	id;
	size_t	num;

	id = philo->id;
	num = philo->info->num_philo;
	pthread_mutex_lock(&philo->info->fork[id - 1]);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->info->fork[id % num]);
	print_action(philo, "has taken a fork");
	return ;
}

void	start_eating(t_philo *philo)
{
	size_t	id;
	size_t	num;

	id = philo->id;
	num = philo->info->num_philo;
	print_action(philo, "is eating");
	philo->info->time_stamp = get_millisecond();
	philo->time_last_ate = get_millisecond();
	usleep(philo->info->time_eat * 1000);
	pthread_mutex_unlock(&philo->info->fork[id - 1]);
	pthread_mutex_unlock(&philo->info->fork[id % num]);
	return ;
}

void	start_sleeping(t_philo *philo)
{
	philo->info->time_stamp = get_millisecond();
	print_action(philo, "is sleeping");
	usleep(philo->info->time_sleep * 1000);
	return ;
}

void	*control_philo(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2 == 1)
		usleep(1000);
	while (true)
	{
		take_forks(philo);
		start_eating(philo);
		start_sleeping(philo);
	}
	return (NULL);
}
