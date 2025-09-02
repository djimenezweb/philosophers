/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:19:02 by danielji          #+#    #+#             */
/*   Updated: 2025/08/22 10:50:44 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define TAKE_FORK 1
# define EAT 2
# define DOWN_FORK 3
# define SLEEP 4
# define THINK 5
# define DIE 6

typedef struct s_config
{
	int				total_philo;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				max_loops;
	pthread_mutex_t	*forks;
	struct s_philo	*philo_array;
}					t_config;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_config		config;
	//long long		last_lunch_time;
}					t_philo;

/* atoi.c */

int			ft_atoi(const char *str);

/* initialization.c */

t_config	init_config(int argc, char *argv[]);
t_philo		init_philo(t_config config, int id);
t_philo		*init_array(t_config config, int n);

/* threads.c */

void		*routine(void *arg);
void		create_threads(t_config config);

/* timestamps.c */

long long	getmilliseconds(void);
void		timestamp(int id, int mode);
void		ft_sleep_ms(int ms);

/* validation.c */

int			arg_validation(int argc, char *argv[]);

#endif