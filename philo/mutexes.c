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
