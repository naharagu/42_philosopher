/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 09:15:17 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/01 12:41:15 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

void	print_action(t_philo *philo, char *action)
{
	size_t	time;

	time = get_millisecond() - philo->info->time_current;
	pthread_mutex_lock(&philo->print);
	printf("%lu %d %s\n", time, philo->id, action);
	pthread_mutex_lock(&philo->print);
}
