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

/* Read mutex-protected `done` value */
int	get_done_value(t_philo *p)
{
	return (get_mutex_value(&p->last_lunch_mtx, &p->done));
}

/* Read mutex-protected `stop` value */
int	get_stop_value(t_ctx *ctx)
{
	return (get_mutex_value(&ctx->stop_mtx, &ctx->stop));
}

/* Read mutex-protected `start` value */
int	get_start_value(t_ctx *ctx)
{
	return (get_mutex_value(&ctx->start_mtx, &ctx->start));
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
