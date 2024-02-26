/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:38:20 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/26 14:32:51 by bekhodad         ###   ########.fr       */
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

int	eating(t_philos *temp, t_philo *aux, int first_fork, int second_fork)
{
	if (check_if_death_happen(temp, temp->philo, temp->id))
		return (1) ;
	if (temp->nottpa == temp->philo->notepme)
		return (1);
	pthread_mutex_lock(&aux->eating[first_fork]);
	printf(YEL"%ld %d has taken a fork" RESET "\n", get_time() - aux->st, temp->id);
	pthread_mutex_lock(&aux->eating[second_fork]);
	printf(YEL"%ld %d has taken a fork" RESET "\n", get_time() - aux->st, temp->id);
	printf(BLU"%ld %d is eating" RESET "\n", get_time() - aux->st, temp->id);
	temp->nottpa += 1;
	temp->lttpa = get_time();
	usleep(aux->tte * 1000);
	pthread_mutex_unlock(&aux->eating[second_fork]);
	pthread_mutex_unlock(&aux->eating[first_fork]);
	return (0);
}

int	sleeping_thinking(t_philos *temp, t_philo *aux)
{
	if (check_if_death_happen(temp, temp->philo, temp->id))
		return (1) ;
	printf(MAG"%ld %d is sleeping" RESET "\n", get_time() - aux->st, temp->id);
	usleep(aux->tts * 1000);
	printf(GRN"%ld %d is thinking" RESET "\n", get_time() - aux->st, temp->id);
	return (0);
}
