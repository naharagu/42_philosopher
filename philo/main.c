/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:49:04 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/01 23:13:43 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

void	check_philo(t_philo *philo)
{
	if ((get_millisecond() - philo->time_last_ate) / 1000 >
		(size_t)philo->info->time_die)
	{
		// philo->info->end = 1;
		print_action(philo, "is died");
		// pthread_mutex_lock(&philo->info->mtx_end);
	}
}

void	check_philo_death(t_info *info)
{
	int	i;

	while (true)
	{
		usleep(2000);
		i = 0;
		while (i < info->num_philo)
		{
			check_philo(&info->philo[i]);
			i++;
		}
	}
	return ;
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
	check_philo_death(info);
	exit_and_free(1, info);
}
