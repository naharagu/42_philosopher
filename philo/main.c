/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:49:04 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/14 09:13:25 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

int	philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		if (pthread_create(&info->philo[i].thread_phil, NULL, control_philo, \
		&info->philo[i]))
			return (-1);
		i++;
	}
	if (pthread_create(&info->thread_moni, NULL, monitor_philo, info))
		return (-1);
	i = 0;
	while (i < info->num_philo)
	{
		pthread_join(info->philo[i].thread_phil, NULL);
		i++;
	}
	pthread_join(info->thread_moni, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	*info;

	if (validate_args(argc, argv) == -1)
		return (1);
	info = malloc(sizeof(t_info));
	if (!info)
		return (1);
	if (init(info, argc, argv) == -1)
		return (1);
	if (philo(info) == -1)
	{
		free_all(info);
		return (1);
	}
	free_all(info);
	return (0);
}
