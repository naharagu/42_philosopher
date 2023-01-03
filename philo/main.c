/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:49:04 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/03 10:39:07 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

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
