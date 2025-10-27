/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danielji <danielji@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:19:06 by danielji          #+#    #+#             */
/*   Updated: 2025/09/04 17:43:09 by danielji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* - Create observer thread
- Create one thread per philosopher
- Set starting time after they are all created
- Wait for philosopher and observer threads to finish
- Call `cleanup` if thread creation or join fails */
void	create_threads(t_ctx *ctx)
{
	int		i;
	t_philo	*p;

	i = 0;
	if (pthread_create(&ctx->observer_thread, NULL, obs_routine, ctx) != 0)
		cleanup(ctx);
	while (i < ctx->n)
	{
		p = &ctx->philo_arr[i];
		if (pthread_create(&p->philo_thread, NULL, philo_routine, p) != 0)
			cleanup(ctx);
		i++;
	}
	//ctx->start_time = get_current_ms();
	pthread_mutex_lock(&ctx->start_mtx);
	ctx->start = 1;
	pthread_mutex_unlock(&ctx->start_mtx);
	if (pthread_join(ctx->observer_thread, NULL) != 0)
		cleanup(ctx);
	i = 0;
	while (i < ctx->n)
	{
		if (pthread_join(ctx->philo_arr[i].philo_thread, NULL) != 0)
			cleanup(ctx);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_ctx	ctx;

	if (arg_validation(argc, argv) < 0)
		return (EXIT_FAILURE);
	if (init_config(&ctx, argc, argv) < 0)
		return (cleanup(&ctx), EXIT_FAILURE);
	create_threads(&ctx);
	cleanup(&ctx);
	return (EXIT_SUCCESS);
}
