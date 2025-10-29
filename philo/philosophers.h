/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:19:02 by danielji          #+#    #+#             */
/*   Updated: 2025/10/26 15:36:24 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define LEFT 0
# define RIGHT 1
# define STOP 1
# define DONE 1
# define CONTINUE 0
# define TAKE_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

typedef struct s_ctx
{
	int				n;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				delay;
	int				max_loops;
	long			start_time;
	pthread_t		observer_thread;
	int				stop;
	pthread_mutex_t	stop_mtx;
	int				start;
	pthread_mutex_t	start_mtx;
	pthread_mutex_t	safe_print_mtx;
	struct s_philo	*philo_arr;
}					t_ctx;

typedef struct s_philo
{
	int				id;
	pthread_t		philo_thread;
	pthread_mutex_t	fork_mtx;
	long			last_lunch;
	pthread_mutex_t	last_lunch_mtx;
	int				loop;
	int				done;
	t_ctx			*ctx;
}					t_philo;

void	cleanup(t_ctx *ctx);
t_philo	init_philo(t_ctx *ctx, int id);
t_philo	*init_philo_array(t_ctx *ctx);
int		init_config(t_ctx *ctx, int argc, char *argv[]);
void	create_threads(t_ctx *ctx);
void	take_fork(pthread_mutex_t *fork, t_ctx *ctx, int id);
int		get_done_value(t_philo *p);
int		get_stop_value(t_ctx *ctx);
int		get_start_value(t_ctx *ctx);
int		get_mutex_value(pthread_mutex_t *mtx, int *ptr);
int		are_all_done(t_ctx *ctx);
int		is_anyone_dead(t_ctx *ctx);
void	*obs_routine(void *arg);
void	single_philo(t_philo *p);
void	take_forks(t_philo *p, pthread_mutex_t *forks[]);
void	eat(t_philo *p);
void	*philo_routine(void *arg);
void	safe_print(t_ctx *ctx, int id, char *str);
long	get_current_ms(void);
void	sleep_ms(int time_ms);
int		ft_atoi(const char *str);
int		arg_validation(int argc, char *argv[]);

#endif
