/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:47:52 by naharagu          #+#    #+#             */
/*   Updated: 2022/12/31 20:40:55 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

int	init_philo(t_info *info)
{
	int	i;

	i = 0;
	info->philo = malloc(sizeof(t_philo) * info->num_philo);
	if (!info->philo)
		exit(0);
	while (i < info->num_philo)
	{
		info->philo[i].id = i;
		info->philo[i].eating = false;
		info->philo[i].time_last_ate = i;
		pthread_mutex_init(&info->philo[i].fork, NULL);
		info->philo[i].info = info;
		i++;
	}
	return (0);
}

int	init(t_info *info, int argc, char **argv)
{
	info->num_philo = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->num_must_eat = ft_atoi(argv[5]);
	else
		info->num_must_eat = -1;
	printf("!num of philos is %d\n", info->num_philo);
	info->time_current = 0;
	init_philo(info);
	return (0);
}
