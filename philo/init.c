/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:47:52 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/21 10:09:00 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

int	init_philo(t_info *info)
{
	int	i;

	i = 0;
	info->philo = malloc(sizeof(t_philo) * info->num_philo);
	if (!info->philo)
		return (-1);
	info->fork = malloc(sizeof(pthread_mutex_t) * info->num_philo);
	if (!info->fork)
		return (-1);
	while (i < info->num_philo)
	{
		info->philo[i].id = i + 1;
		info->philo[i].cnt_times_ate = 0;
		info->philo[i].time_last_start_eating = info->time_start;
		pthread_mutex_init(&info->fork[i], NULL);
		pthread_mutex_init(&info->philo[i].lock_time_last_ate, NULL);
		info->philo[i].info = info;
		i++;
	}
	return (0);
}

int	init(t_info *info, int argc, char **argv)
{
	info->num_philo = ft_atoi(argv[1]);
	info->time_die = (time_t)ft_atoi(argv[2]);
	info->time_eat = (time_t)ft_atoi(argv[3]);
	info->time_sleep = (time_t)ft_atoi(argv[4]);
	info->time_start = get_millisecond() + 1000;
	info->time_stamp = info->time_start;
	if (argc == 6)
		info->num_must_eat = ft_atoi(argv[5]);
	else
		info->num_must_eat = -1;
	info->cnt_finish_eating = 0;
	info->end_flag = false;
	pthread_mutex_init(&info->lock_end, NULL);
	pthread_mutex_init(&info->lock_num_eat, NULL);
	pthread_mutex_init(&info->lock_time_stamp, NULL);
	if (init_philo(info) == -1)
		return (1);
	return (0);
}
