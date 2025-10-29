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

	if (get_stop_value(ctx) == 1)
		return ;
	pthread_mutex_lock(&ctx->safe_print_mtx);
	time_diff = get_current_ms() - ctx->start_time;
	printf("%ld %d %s\n", time_diff, id, str);
	pthread_mutex_unlock(&ctx->safe_print_mtx);
}

/* Return current time in milliseconds */
long	get_current_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/* Suspend execution for an interval `time_ms` in milliseconds.
Accurate version: Sleeps in intervals of 2 milliseconds
(or 0.5ms if less than 5ms remain) until `time_ms` have passed.
Why an accurate version? `usleep()` is not perfectly precise,
it can sleep longer than requested due to OS scheduling. */
void	sleep_ms(int time_ms)
{
	long	start;
	long	time_diff;

	start = get_current_ms();
	while (1)
	{
		time_diff = get_current_ms() - start;
		if (time_diff >= (long)time_ms)
			break ;
		if ((time_ms - time_diff) > 5)
			usleep(2000);
		else
			usleep(500);
	}
}
