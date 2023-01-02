/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sopher.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:49:43 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/02 12:47:06 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOPHER_H
# define SOPHER_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;
typedef struct s_info
{
	int					num_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					num_must_eat;
	size_t				time_stamp;
	size_t				time_start;
	pthread_mutex_t		info_mutex;
	pthread_mutex_t		*fork;
	t_philo				*philo;
}						t_info;
typedef struct s_philo
{
	int					id;
	bool				eating;
	size_t				time_last_ate;
	pthread_t			thread;
	pthread_mutex_t		print;
	t_info				*info;
}						t_philo;

int						validate_args(int argc, char **argv);
int						ft_isdigit(int c);
int						ft_atoi(const char *str);
int						init(t_info *info, int argc, char **argv);
size_t					get_millisecond(void);
void					*control_philo(void *p);
void					print_action(t_philo *philo, char *action);
void					exit_and_free(int n, t_info *info);
void					start_monitor(t_philo *philo);

#endif