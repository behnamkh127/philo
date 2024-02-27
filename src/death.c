/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:38:20 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/27 10:39:38 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_if_death_happen(t_philos *temp, t_philo *aux, int j)
{
	pthread_mutex_lock(&aux->detex);
	if (aux->death == 1)
	{
		if (temp->died)
			printf(RED"%ld %d died" RESET "\n", get_time() - aux->st, j);
		pthread_mutex_unlock(&aux->detex);
		return (1);
	}
	pthread_mutex_unlock(&aux->detex);
	return (0);
}
