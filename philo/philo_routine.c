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

/* If there's a single philosopher he takes fork and dies */
void	single_philo(pthread_mutex_t *fork, t_ctx *ctx)
{
	pthread_mutex_lock(fork);
	safe_print(ctx, 1, TAKE_FORK);
	pthread_mutex_unlock(fork);
	sleep_ms(ctx->tt_die);
}

/* - Every philosopher takes their right fork, except for the last one,
who takes the fork from the first philosopher.
- Even philosophers start taking LEFT fork, then RIGHT
- Odd philosophers start taking RIGHT fork, then LEFT*/
void	take_forks(t_philo *p, pthread_mutex_t *forks[])
{
	forks[LEFT] = &p->fork_mtx;
	if (p->id == p->ctx->n)
		forks[RIGHT] = &p->ctx->philo_arr[0].fork_mtx;
	else
		forks[RIGHT] = &p->ctx->philo_arr[p->id].fork_mtx;
	if (p->id % 2 == 0)
	{
		take_fork(forks[LEFT], p->ctx, p->id);
		take_fork(forks[RIGHT], p->ctx, p->id);
	}
	else
	{
		take_fork(forks[RIGHT], p->ctx, p->id);
		take_fork(forks[LEFT], p->ctx, p->id);
	}
}

/* Don't run if `stop == 1`
Take forks, set last lunch time and increment 1 loop, put down forks */
void	eat(t_philo *p)
{
	pthread_mutex_t	*forks[2];

	if (get_stop_value(p->ctx) == 1)
		return ;
	take_forks(p, forks);
	safe_print(p->ctx, p->id, EAT);
	pthread_mutex_lock(&p->last_lunch_mtx);
	p->last_lunch = get_current_ms();
	p->loop = p->loop + 1;
	if ((p->ctx->max_loops) > 0 && (p->loop >= p->ctx->max_loops))
		p->done = 1;
	pthread_mutex_unlock(&p->last_lunch_mtx);
	sleep_ms(p->ctx->tt_eat);
	pthread_mutex_unlock(forks[LEFT]);
	pthread_mutex_unlock(forks[RIGHT]);
}

//TODO: POSIBLES APORTACIONES
/* Retrasar filósofo nº 3 si total 3

	if (p->id % 2 == 0 || (p->ctx->n == 3 && p->id == 3))
		sleep_ms(p->ctx->delay - 10);

	if (p->id % 2 != 0 && p->id == p->ctx->n)
		usleep(100); 

	Añadir retraso 1 ms al final sólo pares
	if (p->ctx->n % 2 == 0)
		sleep_ms(1);
*/

/* - Wait in 100 microsecond increments until `start` is set to `1`
- Run until `stop` returns `1`
- Hold even philosophers to let the odd ones start before
- Call `eat`, `sleep` and `think` subroutines */
void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (get_mutex_value(&p->ctx->start_mtx, &p->ctx->start) == 0)
		usleep(100);
	if (p->ctx->n == 1)
		return (single_philo(&p->fork_mtx, p->ctx), NULL);
	if (p->id % 2 == 0)
		sleep_ms(p->ctx->tt_eat - 1);
	while (get_stop_value(p->ctx) == 0)
	{
		if (p->done)
			break ;
		eat(p);
		if (get_stop_value(p->ctx) == 1)
			break ;
		safe_print(p->ctx, p->id, SLEEP);
		sleep_ms(p->ctx->tt_sleep);
		if (get_stop_value(p->ctx) == 1)
			break ;
		safe_print(p->ctx, p->id, THINK);
	}
	return (NULL);
}
