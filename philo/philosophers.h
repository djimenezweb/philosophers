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

# define L 0
# define LEFT 0
# define R 1
# define RIGHT 1
# define TAKE_FORK 1
# define EAT 2
# define DOWN_FORK 3
# define SLEEP 4
# define THINK 5
# define DIE 6

typedef struct s_config
{
	long			start_time;
	int				total_philo;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				max_loops;
	struct s_philo	*philo_arr;
}					t_config;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	fork;
	t_config		*config;
	//long			last_lunch_time;
}					t_philo;

#endif
void	cleanup(t_config *config);
t_philo	init_philo(t_config *config, int id);
t_philo	*init_philo_array(t_config *config);
int		init_config(t_config *config, int argc, char *argv[]);
void	create_threads(t_config *config);
void	take_forks(t_philo *p, pthread_mutex_t *fork[]);
void	eat(t_philo *p);
void	*routine(void *arg);
void	timestamp(int id, int mode, long start);
long	getmilliseconds(void);
void	ft_sleep_ms(int ms);
int		ft_atoi(const char *str);
int		arg_validation(int argc, char *argv[]);
