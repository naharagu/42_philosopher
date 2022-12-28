/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:47:52 by naharagu          #+#    #+#             */
/*   Updated: 2022/12/28 12:15:44 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

int	validate_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 || argc != 6)
		return (-1);
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	init(t_info *info)
{
	info->total_ate = 0;
	return (0);
}
