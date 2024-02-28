/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:38:20 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/28 13:23:57 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_if_death_happen(t_philo *temp, int j)
{
	pthread_mutex_lock(&temp->philos->detex);
	if (temp->philos->death == 1)
	{
		if (temp->died)
			printf(RED"%ld %d died"RESET"\n", get_time() - temp->philos->st, j);
		pthread_mutex_unlock(&temp->philos->detex);
		return (1);
	}
	pthread_mutex_unlock(&temp->philos->detex);
	return (0);
}
