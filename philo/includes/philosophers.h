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

typedef struct s_config
{
	int				number;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				max_loops;
	struct s_philo	*philo_array;
}					t_config;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	t_config	config;
}				t_philo;

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

void		timestamp(int id, char *str);

/* validation.c */
int			arg_validation(int argc, char *argv[]);

#endif