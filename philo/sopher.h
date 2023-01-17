/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sopher.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:49:43 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/17 20:16:16 by naharagu         ###   ########.fr       */
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
	time_t				time_die;
	time_t				time_eat;
	time_t				time_sleep;
	int					num_must_eat;
	int					cnt_finish_eating;
	time_t				time_stamp;
	time_t				time_start;
	bool				end_flag;
	pthread_mutex_t		*fork;
	pthread_mutex_t		lock_end;
	pthread_mutex_t		lock_num_eat;
	pthread_mutex_t		lock_time_stamp;
	t_philo				*philo;
}						t_info;
typedef struct s_philo
{
	int					id;
	int					cnt_times_ate;
	time_t				time_last_start_eating;
	pthread_mutex_t		lock_time_last_ate;
	pthread_t			thr;
	t_info				*info;
}						t_philo;

int						validate_args(int argc, char **argv);
int						ft_isdigit(int c);
int						ft_atoi(const char *str);
int						init(t_info *info, int argc, char **argv);
time_t					get_millisecond(void);
void					*philo(void *p);
int						start_monitor(t_info *info);
void					*monitor_philo(void *p);
void					print_action(t_philo *philo, char *action);
void					free_all(t_info *info);

#endif