/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:44:56 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/28 11:57:53 by bekhodad         ###   ########.fr       */
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
	if (!philos)
		return (1);
	if (philos->nop == 1)
		return (one_philo(philos));
	if (init_mutex(philos))
		return (1);
	philo = init_philos(philos);
	if (!philo)
		return (1);
	if (threads_create(philos, philo))
		return (1);
	free_func(philos, philo);
	return (0);
}
