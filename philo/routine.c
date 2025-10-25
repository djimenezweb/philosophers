/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:07:07 by danielji          #+#    #+#             */
/*   Updated: 2025/10/24 10:07:07 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* - If there's a single philosopher he takes fork and dies
- Even philosophers start taking (locking) the LEFT fork
- Odd philosophers start taking (locking) the RIGHT fork */
void	take_forks(t_philo *p, pthread_mutex_t *forks[])
{
	long	start_time;

	start_time = p->config->start_time;
	if (p->config->total_philo == 1)
	{
		pthread_mutex_lock(&p->fork);
		timestamp(p->id, FORK, start_time);
		ft_sleep_ms(p->config->tt_die);
		// philosopher dies because he can't take the second fork
		pthread_mutex_unlock(&p->fork);
		return ;
	}
	else if (p->id % 2 == 0)
	{
		// Even id: start taking LEFT fork
		pthread_mutex_lock(forks[LEFT]);
		timestamp(p->id, FORK, start_time);
		pthread_mutex_lock(forks[RIGHT]);
		timestamp(p->id, FORK, start_time);
	}
	else
	{
		// Odd id: start taking RIGHT fork
		pthread_mutex_lock(forks[RIGHT]);
		timestamp(p->id, FORK, start_time);
		pthread_mutex_lock(forks[LEFT]);
		timestamp(p->id, FORK, start_time);
	}
}

/* Every philosopher takes their right fork, except for the last one,
who takes the fork from the first philosopher */
pthread_mutex_t	*right_fork(t_philo *p)
{
	if (p->id == p->config->total_philo - 1)
		return (&p->config->philo_arr[0].fork);
	else
		return (&p->config->philo_arr[p->id + 1].fork);
}

/* - Set left and right forks before eating
- Take (lock) the forks
- Wait the specified `tt_eat` time
- Put down (unlock) the forks */
void	eat(t_philo *p)
{
	pthread_mutex_t	*forks[2];

	// SET FORKS:
	forks[LEFT] = &p->fork;
	forks[RIGHT] = right_fork(p);
	// TAKE FORKS:
	take_forks(p, forks);
	timestamp(p->id, EAT, p->config->start_time);
	ft_sleep_ms(p->config->tt_eat);
	// PUT DOWN FORKS:
	pthread_mutex_unlock(forks[LEFT]);
	pthread_mutex_unlock(forks[RIGHT]);
}

/* - Wait until `start_time` is set
- Run a limited amount of loops, indefinitely, or unil any philosopher dies
- Hold even philosophers to let the odd ones start first
- Call `eat`, `sleep` and `think` subroutines */
void	*philo_routine(void *arg)
{
	t_philo	*p;
	int		loop;

	p = (t_philo *)arg;
	while (!p->config->start_time)
		ft_sleep_ms(1);
	loop = 0;
	while (loop < p->config->max_loops)
	{
		if (p->id % 2 == 0)
			ft_sleep_ms(1);

		// EAT
		eat(p);

		// SLEEP
		timestamp(p->id, SLEEP, p->config->start_time);
		ft_sleep_ms(p->config->tt_sleep);

		// THINK
		timestamp(p->id, THINK, p->config->start_time);
		
		loop++;
	}
	return (NULL);
}
