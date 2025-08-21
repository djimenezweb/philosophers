/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:19:02 by danielji          #+#    #+#             */
/*   Updated: 2025/08/21 09:46:45 by danielji         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_config
{
	int	number;
	int	tt_die;
	int	tt_eat;
	int	tt_sleep;
	int	max_loops;
}		t_config;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;

}	t_philo;

/* atoi.c */

int			ft_atoi(const char *str);

/* initialization.c */

t_config	init_config(int argc, char *argv[]);
t_philo		init_philo(int id);
t_philo		*init_array(int n);

/* threads.c */

void		*routine(void *arg);
void		create_threads(int n, t_philo	*array);

#endif