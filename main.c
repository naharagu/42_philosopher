/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:49:04 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/01 12:47:07 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

void	philo(t_info *info)
{
	int	i;

	info->time_current = get_millisecond();
	info->philo->time_last_ate = info->time_current;
	i = 0;
	while (i < info->num_philo)
	{
		// printf("TEST!\n");
		pthread_create(&info->philo[i].thread, NULL, control_philo, \
		info->philo);
		i++;
	}
	i = 0;
	while (i < info->num_philo)
	{
		// printf("TEST2!\n");
		pthread_join(info->philo[i].thread, (void *)info->philo);
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
