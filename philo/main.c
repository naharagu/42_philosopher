/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:49:04 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/03 10:15:41 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

void	monitor_philo(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	while (true)
	{
		if ((get_millisecond() - philo->time_last_ate) > info->time_die)
		{
			info->time_stamp = get_millisecond();
			print_action(philo, "died");
			info->flag_end = true;
		}
		if (info->cnt_finish_must == info->num_must_eat)
			info->flag_end = true;
		if (info->flag_end || philo->flag_must_eat)
			pthread_mutex_unlock(&info->fork[philo->id - 1]);
		if (info->flag_end)
		{
			pthread_mutex_lock(&info->print);
			return ;
		}
		usleep(100);
	}
}

void	start_monitor(t_philo *philo)
{
	pthread_t	moni;

	pthread_create(&moni, NULL, monitor_philo, philo);
	pthread_join(&moni, NULL);
	return ;
}

void	philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		pthread_create(&info->philo[i].thread, NULL, control_philo, \
		&info->philo[i]);
		i++;
	}
	i = 0;
	while (i < info->num_philo)
	{
		pthread_join(info->philo[i].thread, NULL);
		// printf("ID: %d done\n", i + 1);
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
	free_and_exit(info);
}

// __attribute__((destructor))
// static void destructor() {
// 	system("leaks -q philo");
// }