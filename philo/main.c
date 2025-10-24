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

int	main(int argc, char *argv[])
{
	int			status;
	t_config	config;

	if (argc <= 4)
		return (EXIT_FAILURE);
	if (!arg_validation(argc, argv))
		return (EXIT_FAILURE);
	status = init_config(&config, argc, argv);
	if (status != 0)
		return (cleanup(&config), EXIT_FAILURE);
		// TO DO: free something else?
	status = create_threads(&config);
	if (status != 0)
		return (cleanup(&config), EXIT_FAILURE);
		// TO DO: free something else?
	cleanup(&config);
	return (EXIT_SUCCESS);
}
