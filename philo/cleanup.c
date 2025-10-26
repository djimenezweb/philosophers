/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:42:58 by danielji          #+#    #+#             */
/*   Updated: 2025/09/04 17:43:09 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Destroy initialized mutexes and free allocated memory */
void	cleanup(t_ctx *ctx)
{
	int	i;
	int	n;

	i = 0;
	n = ctx->n;
	while (i < n)
	{
		pthread_mutex_destroy(&ctx->philo_arr[i].fork_mtx);
		pthread_mutex_destroy(&ctx->philo_arr[i].last_lunch_mtx);
		i++;
	}
	free(ctx->philo_arr);
	pthread_mutex_destroy(&ctx->stop_mtx);
	pthread_mutex_destroy(&ctx->safe_print_mtx);
	ctx->philo_arr = NULL;
}
