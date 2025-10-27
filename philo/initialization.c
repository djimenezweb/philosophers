/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 09:42:37 by danielji          #+#    #+#             */
/*   Updated: 2025/08/22 10:46:37 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* - Assign `id` and reference to `ctx` to each philosopher
- Set `last_lunch` to current time
- Initalize `fork_mtx` mutex
- Initialize `last_lunch_mtx` mutex
- Return philosopher */
t_philo	init_philo(t_ctx *ctx, int id)
{
	t_philo	p;

	p.id = id;
	p.ctx = ctx;
	p.last_lunch = get_current_ms();
	p.loop = 0;
	p.done = 1;
	pthread_mutex_init(&p.fork_mtx, NULL);
	pthread_mutex_init(&p.last_lunch_mtx, NULL);
	return (p);
}

/* Allocate memory and return an array of initialized philosophers */
t_philo	*init_philo_array(t_ctx *ctx)
{
	int		i;
	int		n;
	t_philo	*arr;

	n = ctx->n;
	arr = (t_philo *)malloc(sizeof(t_philo) * n);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < n)
	{
		arr[i] = init_philo(ctx, i + 1);
		i++;
	}
	return (arr);
}

/* - Initialize `t_ctx` structure
- Initialize array of philosophers 
- Initialize `stop_mtx` and `safe_print_mtx` mutexes
- Return `0` on success, `-1` on error*/
int	init_config(t_ctx *ctx, int argc, char *argv[])
{
	ctx->n = ft_atoi(argv[1]);
	ctx->tt_die = ft_atoi(argv[2]);
	ctx->tt_eat = ft_atoi(argv[3]);
	ctx->tt_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		ctx->max_loops = ft_atoi(argv[5]);
	else
		ctx->max_loops = -1;
	ctx->philo_arr = init_philo_array(ctx);
	if (!ctx->philo_arr)
		return (-1);
	ctx->start_time = get_current_ms();
	ctx->stop = 0;
	ctx->start = 0;
	pthread_mutex_init(&ctx->stop_mtx, NULL);
	pthread_mutex_init(&ctx->start_mtx, NULL);
	pthread_mutex_init(&ctx->safe_print_mtx, NULL);
	return (0);
}
