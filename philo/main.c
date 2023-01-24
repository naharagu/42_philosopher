/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:49:04 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/24 09:25:06 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

int	start_philo(t_info *info)
{
	int		i;
	int		j;
	bool	error_flag;

	i = -1;
	error_flag = false;
	while (++i < info->num_philo)
	{
		if (pthread_create(&info->philo[i].thr, NULL, control_philo,
				&info->philo[i]))
		{
			error_flag = true;
			break ;
		}
	}
	if (start_monitor(info) == -1)
		error_flag = true;
	j = 0;
	while (j < i)
		pthread_join(info->philo[j++].thr, NULL);
	if (error_flag)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (validate_args(argc, argv) == -1)
		return (1);
	if (init(&info, argc, argv) == -1)
		return (1);
	if (start_philo(&info) == -1)
	{
		free_all(&info);
		return (1);
	}
	free_all(&info);
	return (0);
}
