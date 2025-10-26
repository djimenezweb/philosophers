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

# define LEFT 0
# define RIGHT 1
# define TAKE_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died < = = = = = = = = = = = = = = = = = = = ="

typedef struct s_config
{
	long			start_time;
	int				total_philo;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				max_loops;
	pthread_t		observer_th;
	int				stop_val;
	pthread_mutex_t	stop_mtx;
	struct s_philo	*philo_arr;
}					t_config;

typedef struct s_philo
{
	int				id;
	int				is_dead;
	pthread_t		philo_th;
	pthread_mutex_t	fork;
	long			last_lunch;
	pthread_mutex_t	last_lunch_mtx;
	t_config		*config;
}					t_philo;

void			cleanup(t_config *config);
t_philo			init_philo(t_config *config, int id);
t_philo			*init_philo_array(t_config *config);
int				init_config(t_config *config, int argc, char *argv[]);
void			join_threads(t_config *config);
void			create_threads(t_config *config);
int				main(int argc, char *argv[]);
int				is_any_philo_dead(t_config *config);
void			*obs_routine(void *arg);
void			take_forks(t_philo *p, pthread_mutex_t *forks[]);
pthread_mutex_t	*right_fork(t_philo *p);
void			philo_eat(t_philo *p);
void			philo_sleep(t_philo *p);
void			philo_think(t_philo *p);
int				get_stop(t_config *config);
void			set_stop(t_config *config, int value);
void			*philo_routine(void *arg);
void			timestamp(int id, char *str, long start);
long			getmilliseconds(void);
void			ft_sleep_ms(int ms);
int				ft_atoi(const char *str);
int				arg_validation(int argc, char *argv[]);

#endif
