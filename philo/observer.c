/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 13:10:34 by danielji          #+#    #+#             */
/*   Updated: 2025/10/25 13:10:39 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// TODO: Una función que compruebe si todos los filos tienen `done == 1` 

/* Iterate through array of philosophers and check if anyone is dead
- Lock `last_lunch_mtx` to protect read
- If any philo is dead, set `stop` to `1` and return `1`
- Return `0` if every philosopher is alive */
int	should_stop(t_ctx *ctx)
{
	int		i;
	long	time_diff;

	i = 0;
	while (i < ctx->n)
	{
		pthread_mutex_lock(&ctx->philo_arr[i].last_lunch_mtx);
		if (ctx->philo_arr[i].done == 1)
		{
			pthread_mutex_unlock(&ctx->philo_arr[i].last_lunch_mtx);
			return (1);
		}
		time_diff = get_current_ms() - ctx->philo_arr[i].last_lunch;
		if (time_diff > ctx->tt_die)
		{
			pthread_mutex_unlock(&ctx->philo_arr[i].last_lunch_mtx);
			safe_print(ctx, ctx->philo_arr[i].id, DIE);
			pthread_mutex_lock(&ctx->stop_mtx);
			ctx->stop = 1;
			pthread_mutex_unlock(&ctx->stop_mtx);
			return (1);
		}
		pthread_mutex_unlock(&ctx->philo_arr[i].last_lunch_mtx);
		i++;
	}
	return (0);
}

/* Run until `should_stop` returns `1` */
void	*obs_routine(void *arg)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)arg;
	while (1)
	{
		if (should_stop(ctx) == 1)
			break ;
	}
	return (NULL);
}
