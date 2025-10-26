/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:07:07 by danielji          #+#    #+#             */
/*   Updated: 2025/10/26 15:33:23 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Philosopher dies because he can't take the second fork */
void	single_philo(pthread_mutex_t *fork, t_config *config)
{
	pthread_mutex_lock(fork);
	safe_print(config, 1, TAKE_FORK);
	ft_sleep_ms(config->tt_die);
	config->philo_arr[0].is_dead = 1;
	safe_print(config, config->philo_arr[0].id, DIE);
	pthread_mutex_unlock(fork);
	return ;
}

/* Take (mutex lock) fork */
void	take_fork(pthread_mutex_t *fork, t_config *config, int id)
{
	pthread_mutex_lock(fork);
	safe_print(config, id, TAKE_FORK);
}

/* Every philosopher takes their right fork, except for the last one,
who takes the fork from the first philosopher */
pthread_mutex_t	*select_right_fork(t_philo *p)
{
	if (p->id == p->config->total_philo - 1)
		return (&p->config->philo_arr[0].fork);
	else
		return (&p->config->philo_arr[p->id + 1].fork);
}

/* - Select left and right forks before eating
- Take (lock) forks
- If there's a single philosopher he takes fork and dies
- Even philosophers start taking (locking) LEFT fork, then RIGHT
- Odd philosophers start taking (locking) RIGHT fork, then LEFT
- Wait the specified `tt_eat` time
- Put down (unlock) forks */
void	eat(t_philo *p)
{
	pthread_mutex_t	*forks[2];

	forks[LEFT] = &p->fork;
	forks[RIGHT] = select_right_fork(p);
	if (p->config->total_philo == 1)
		single_philo(forks[LEFT], p->config);
	else if (p->id % 2 == 0)
	{
		take_fork(forks[LEFT], p->config, p->id);
		take_fork(forks[RIGHT], p->config, p->id);
	}
	else
	{
		take_fork(forks[RIGHT], p->config, p->id);
		take_fork(forks[LEFT], p->config, p->id);
	}
	safe_print(p->config, p->id, EAT);
	ft_sleep_ms(p->config->tt_eat);
	pthread_mutex_unlock(forks[LEFT]);
	pthread_mutex_unlock(forks[RIGHT]);
}

/* - Wait until `start_time` is set
- Run until `get_stop` returns `1`
- Hold even philosophers 1ms to let the odd ones start before
- Call `eat`, `sleep` and `think` subroutines */
void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (!p->config->start_time)
		ft_sleep_ms(1);
	while (get_stop(p->config) == 0)
	{
		if (p->id % 2 == 0)
			ft_sleep_ms(1);
		eat(p);
		safe_print(p->config, p->id, SLEEP);
		ft_sleep_ms(p->config->tt_sleep);
		safe_print(p->config, p->id, THINK);
	}
	return (NULL);
}
