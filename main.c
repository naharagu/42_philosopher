/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:49:04 by naharagu          #+#    #+#             */
/*   Updated: 2022/12/28 12:15:39 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

void	philo(void)
{
}

int	main(int argc, char **argv)
{
	t_info	*info;

	if (validate_args(argc, argv) == -1)
		exit(0);
	info = malloc(sizeof(t_info));
	if (!info)
		exit(0);
}
