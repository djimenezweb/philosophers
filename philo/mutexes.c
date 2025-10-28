/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:16:44 by danielji          #+#    #+#             */
/*   Updated: 2025/10/28 11:16:44 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

/* - Read mutex-protected `stop` and return it */
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
