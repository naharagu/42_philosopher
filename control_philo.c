/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 20:57:03 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/01 12:47:55 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_right);
	print_action(philo, "has taken a fork\n");
	pthread_mutex_lock(&philo->fork_left);
	print_action(philo, "has taken a fork\n");
	return ;
}

void	*control_philo(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2 == 1)
		usleep(1000);
	while (true)
	{
		take_forks(philo);
		// start_eating(philo);
		// start_sleeping(philo);
		// pthread_mutex_lock(philo);
	}
	return (NULL);
}
