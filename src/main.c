/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:44:56 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/27 19:13:14 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_philo			*philo;
	t_philos		*philos;

	if (check_values(ac, av))
		return (1);
	philos = initialize(av);
	if (philos->nop == 1)
		return (one_philo(philos));
	init_mutex(philos);
	philo = init_philos(philos);
	threads_create(philos, philo);
	free_func(philos, philo);
	return (0);
}
