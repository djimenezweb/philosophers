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
void	single_philo(pthread_mutex_t *fork, t_ctx *ctx)
{
	pthread_mutex_lock(fork);
	safe_print(ctx, 1, TAKE_FORK);
	sleep_ms(ctx->tt_die);
	safe_print(ctx, ctx->philo_arr[0].id, DIE);
	pthread_mutex_unlock(fork);
	return ;
}

/* Take fork (lock mutex) */
void	take_fork(pthread_mutex_t *fork, t_ctx *ctx, int id)
{
	pthread_mutex_lock(fork);
	safe_print(ctx, id, TAKE_FORK);
}

/* Put down fork (unlock mutex) */
void	put_down_forks(pthread_mutex_t *forks[])
{
	pthread_mutex_unlock(forks[LEFT]);
	pthread_mutex_unlock(forks[RIGHT]);
}

/* Select forks and take them */
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

/* - Select left and right forks before eating
- Every philosopher takes their right fork, except for the last one,
who takes the fork from the first philosopher
- Take (lock) forks
- If there's a single philosopher he takes fork and dies
- Even philosophers start taking (locking) LEFT fork, then RIGHT
- Odd philosophers start taking (locking) RIGHT fork, then LEFT
- Wait the specified `tt_eat` time
- Put down (unlock) forks */
void	eat(t_philo *p)
{
	pthread_mutex_t	*forks[2];

	if (p->ctx->n == 1)
		single_philo(&p->fork_mtx, p->ctx);

	take_forks(p, forks);
	safe_print(p->ctx, p->id, EAT);
	pthread_mutex_lock(&p->last_lunch_mtx);
	p->last_lunch = get_current_ms();
	p->loop = p->loop + 1;
	pthread_mutex_unlock(&p->last_lunch_mtx);
	sleep_ms(p->ctx->tt_eat);
	put_down_forks(forks);
}

/* - Read mutex-protected `stop` and return it
- If it's `0`, simulation should continue
- If it's `1`, simulation should stop */
int	get_stop_value(t_ctx *ctx)
{
	return (get_mutex_value(&ctx->stop_mtx, &ctx->stop));
}

/* Return mutex-protected int `value` */
int	get_mutex_value(pthread_mutex_t *mtx, int *ptr)
{
	int	value;

	pthread_mutex_lock(mtx);
	value = *ptr;
	pthread_mutex_unlock(mtx);
	return (value);
}

/* - Wait until `start` is set to `1`
- Run until `stop` returns `1`
- Hold even philosophers 1ms to let the odd ones start before
- Call `eat`, `sleep` and `think` subroutines */
void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (get_mutex_value(&p->ctx->start_mtx, &p->ctx->start) == 0)
		sleep_ms(1);
	// TODO: Retrasar filósofos pares o filósofo 3 si total 3
	// TODO: delay es tt_eat, pero si tt_eat es mayor que tt_sleep, entonces delay es tt_sleep
	int delay = p->ctx->tt_eat - 10;
	if (p->ctx->tt_eat > p->ctx->tt_sleep)
		delay = p->ctx->tt_sleep;
	if (p->id % 2 == 0)
		sleep_ms(delay);
	if (p->ctx->n == 3 && p->id == 3)
		sleep_ms(delay);
	while (get_mutex_value(&p->ctx->stop_mtx, &p->ctx->stop) == 0)
	{

		pthread_mutex_lock(&p->last_lunch_mtx);
		if ((p->ctx->max_loops) > 0 && (p->loop >= p->ctx->max_loops))
		{
			p->done = 1;
			pthread_mutex_unlock(&p->last_lunch_mtx);
			return (NULL);
		}
		pthread_mutex_unlock(&p->last_lunch_mtx);

		eat(p);

		pthread_mutex_lock(&p->last_lunch_mtx);
		if ((p->ctx->max_loops) > 0 && (p->loop >= p->ctx->max_loops))
		{
			p->done = 1;
			pthread_mutex_unlock(&p->last_lunch_mtx);
			return (NULL);
		}
		pthread_mutex_unlock(&p->last_lunch_mtx);
		if (get_mutex_value(&p->ctx->stop_mtx, &p->ctx->stop) == 1)
			break ;
		safe_print(p->ctx, p->id, SLEEP);
		sleep_ms(p->ctx->tt_sleep);
		if (get_mutex_value(&p->ctx->stop_mtx, &p->ctx->stop) == 1)
			break ;
		safe_print(p->ctx, p->id, THINK);
	}
	return (NULL);
}
