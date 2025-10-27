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
	//ctx->philo_arr[0].is_dead = 1;
	safe_print(ctx, ctx->philo_arr[0].id, DIE);
	pthread_mutex_unlock(fork);
	return ;
}

/* Take (mutex lock) fork */
void	take_fork(pthread_mutex_t *fork, t_ctx *ctx, int id)
{
	pthread_mutex_lock(fork);
	safe_print(ctx, id, TAKE_FORK);
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
	safe_print(p->ctx, p->id, EAT);
	pthread_mutex_lock(&p->last_lunch_mtx);
	p->last_lunch = get_current_ms();
	pthread_mutex_unlock(&p->last_lunch_mtx);
	sleep_ms(p->ctx->tt_eat);
	pthread_mutex_unlock(forks[LEFT]);
	pthread_mutex_unlock(forks[RIGHT]);
}

/* - Read mutex-protected `stop` and return it
- If it's `0`, simulation should continue
- If it's `1`, simulation should stop */
/* int	get_stop_value(t_ctx *ctx)
{
	int	value;

	pthread_mutex_lock(&ctx->stop_mtx);
	value = ctx->stop;
	pthread_mutex_unlock(&ctx->stop_mtx);
	return (value);
} */

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
	if (p->id % 2 == 0)
		sleep_ms(p->ctx->tt_eat);
	while (get_mutex_value(&p->ctx->stop_mtx, &p->ctx->stop) == 0)
	{
		eat(p);
		if (get_mutex_value(&p->ctx->stop_mtx, &p->ctx->stop) == 1)
			break ;
		safe_print(p->ctx, p->id, SLEEP);
		sleep_ms(p->ctx->tt_sleep);
		if (get_mutex_value(&p->ctx->stop_mtx, &p->ctx->stop) == 1)
			break ;
		safe_print(p->ctx, p->id, THINK);
		//sleep_ms(p->ctx->tt_die - p->ctx->tt_eat - p->ctx->tt_sleep - 20);
	}
	return (NULL);
}
