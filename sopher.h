/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sopher.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:49:43 by naharagu          #+#    #+#             */
/*   Updated: 2022/12/28 12:15:25 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOPHER_H
# define SOPHER_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_info
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				total_ate;
	unsigned long	time;
}					t_info;

int					validate_args(int argc, char **argv);
int					ft_isdigit(int c);
int					ft_atoi(const char *str);

#endif