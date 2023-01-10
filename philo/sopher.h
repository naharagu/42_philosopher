/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sopher.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 09:49:43 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/10 22:01:45 by naharagu         ###   ########.fr       */
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
	int					num_finish_must;
	size_t				time_stamp;
	size_t				time_start;
	bool				flag_end;
	pthread_mutex_t		*fork;
	pthread_mutex_t		print;
	t_philo				*philo;
}						t_info;
typedef struct s_philo
{
	int					id;
	int					cnt_times_ate;
	size_t				time_last_ate;
	pthread_t			thread;
	t_info				*info;
}						t_philo;

int						validate_args(int argc, char **argv);
int						ft_isdigit(int c);
int						ft_atoi(const char *str);
int						init(t_info *info, int argc, char **argv);
size_t					get_millisecond(void);
void					*control_philo(void *p);
void					start_monitor(t_philo *philo);
void					print_action(t_philo *philo, char *action);
void					start_monitor(t_philo *philo);
void					free_all(t_info *info);

#endif