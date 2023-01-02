/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:49:04 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/02 12:36:47 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

void	monitor_philo(t_philo *philo)
{
	if ((get_millisecond() - philo->time_last_ate)
		> philo->info->time_die)
	{
		print_action(philo, "is died");
		pthread_mutex_unlock(&philo->info->fork[philo->id - 1]);
		// pthread_join(philo->thread, NULL);
	}
}

void	philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		pthread_create(&info->philo[i].thread, NULL, control_philo,
				&info->philo[i]);
		i++;
	}
	i = 0;
	while (i < info->num_philo)
	{
		pthread_join(info->philo[i].thread, NULL);
		i++;
	}
	return ;
}

int	main(int argc, char **argv)
{
	t_info	*info;

	if (validate_args(argc, argv) == -1)
		exit(0);
	info = malloc(sizeof(t_info));
	if (!info)
		exit(0);
	init(info, argc, argv);
	philo(info);
	exit_and_free(1, info);
}
