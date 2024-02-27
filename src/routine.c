/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:16:08 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/27 19:06:18 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(void *arg)
{
	t_philo	*temp;
	int		first_fork;
	int		second_fork;
	
	temp = (t_philo *)arg;
	if (temp->id == 1)
	{
		first_fork = temp->id;
		second_fork = temp->id - 1;
	}
	else
	{
		first_fork = temp->id - 1;
		second_fork = temp->id % temp->philos->nop;	
	}
	while (1)
	{
		if (check_if_death_happen(temp, temp->philos, temp->id))
			break ;
		if (fork_taking(temp, temp->philos, first_fork, second_fork))
			break;
		if (sleeping_thinking(temp, temp->philos))
			break;
	}
	return NULL;
}


int	fork_taking(t_philo *temp, t_philos *aux, int first_fork, int second_fork)
{
	if (check_if_death_happen(temp, temp->philos, temp->id))
		return (1) ;
	pthread_mutex_lock(&(aux->detex));
	if (temp->nottpa == temp->philos->notepme)
	{
		pthread_mutex_unlock(&(aux->detex));
		return (1);
	}
	pthread_mutex_unlock(&(aux->detex));
	pthread_mutex_lock(&aux->eating[first_fork]);
	printf(YEL"%ld %d has taken a fork" RESET "\n", get_time() - aux->st, temp->id);
	if (check_if_death_happen(temp, temp->philos, temp->id))
	{
		pthread_mutex_unlock(&aux->eating[first_fork]);
		return (1) ;
	}
	pthread_mutex_lock(&aux->eating[second_fork]);
	if (eating(temp, aux, first_fork, second_fork))
		return (1);
	pthread_mutex_unlock(&aux->eating[second_fork]);
	pthread_mutex_unlock(&aux->eating[first_fork]);
	return (0);
}

int eating(t_philo *temp, t_philos *aux, int first_fork, int second_fork)
{	
	if (check_if_death_happen(temp, temp->philos, temp->id))
	{
		pthread_mutex_unlock(&aux->eating[second_fork]);
		pthread_mutex_unlock(&aux->eating[first_fork]);
		return (1) ;
	}
	printf(YEL"%ld %d has taken a fork" RESET "\n", get_time() - aux->st, temp->id);
	printf(BLU"%ld %d is eating" RESET "\n", get_time() - aux->st, temp->id);
	pthread_mutex_lock(&(aux->detex));
	temp->nottpa += 1;
	temp->lttpa = get_time();
	pthread_mutex_unlock(&(aux->detex));
	msleep(aux->tte);
	return (0);
}

int	sleeping_thinking(t_philo *temp, t_philos *aux)
{
	if (check_if_death_happen(temp, temp->philos, temp->id))
		return (1) ;
	printf(MAG"%ld %d is sleeping" RESET "\n", get_time() - aux->st, temp->id);
	msleep(aux->tts);
	printf(GRN"%ld %d is thinking" RESET "\n", get_time() - aux->st, temp->id);
	return (0);
}