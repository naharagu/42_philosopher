/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 09:15:17 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/01 23:01:03 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

void	print_action(t_philo *philo, char *action)
{
	size_t	time;

	time = philo->info->time_stamp - philo->info->time_start;
	printf("%lu %d %s\n", time, philo->id, action);
}
