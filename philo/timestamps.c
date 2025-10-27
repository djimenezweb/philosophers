/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 09:51:42 by danielji          #+#    #+#             */
/*   Updated: 2025/08/22 12:55:14 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* - Lock `safe_print_mtx` mutex before printing
- Print change in status and current milliseconds since the start
- Unock mutex after printing */
void	safe_print(t_ctx *ctx, int id, char *str)
{
	long	time_diff;

	pthread_mutex_lock(&ctx->safe_print_mtx);
	time_diff = get_current_ms() - ctx->start_time;
	printf("%ld %d %s\n", time_diff, id, str);
	pthread_mutex_unlock(&ctx->safe_print_mtx);
}

/* Return current Epoch time in milliseconds */
long	get_current_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/* Suspend execution for an interval in milliseconds */
void	sleep_ms(int ms)
{
	usleep(ms * 1000);
}
