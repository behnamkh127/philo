/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:16:08 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/28 13:43:39 by bekhodad         ###   ########.fr       */
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
		if (check_if_death_happen(temp, temp->id))
			break ;
		if (fork_taking(temp, first_fork, second_fork))
			break ;
		if (sleeping_thinking(temp, temp->philos))
			break ;
	}
	return (NULL);
}

int	fork_taking(t_philo *temp, int first_fork, int second_fork)
{
	if (check_if_death_happen(temp, temp->id))
		return (1);
	pthread_mutex_lock(&(temp->philos->detex));
	if (temp->nottpa == temp->philos->notepme)
	{
		pthread_mutex_unlock(&(temp->philos->detex));
		return (1);
	}
	pthread_mutex_unlock(&(temp->philos->detex));
	pthread_mutex_lock(&temp->philos->fork[first_fork]);
	printf(Y"%ld %d has taken a fork"RESET"\n",
		get_time() - temp->philos->st, temp->id);
	if (check_if_death_happen(temp, temp->id))
	{
		pthread_mutex_unlock(&temp->philos->fork[first_fork]);
		return (1);
	}
	pthread_mutex_lock(&temp->philos->fork[second_fork]);
	if (eating(temp, first_fork, second_fork))
		return (1);
	pthread_mutex_unlock(&temp->philos->fork[second_fork]);
	pthread_mutex_unlock(&temp->philos->fork[first_fork]);
	return (0);
}

int	eating(t_philo *temp, int first_fork, int second_fork)
{
	if (check_if_death_happen(temp, temp->id))
	{
		pthread_mutex_unlock(&temp->philos->fork[second_fork]);
		pthread_mutex_unlock(&temp->philos->fork[first_fork]);
		return (1);
	}
	printf(Y"%ld %d has taken a fork"RESET"\n",
		get_time() - temp->philos->st, temp->id);
	printf(BLU"%ld %d is eating" RESET "\n",
		get_time() - temp->philos->st, temp->id);
	pthread_mutex_lock(&(temp->philos->detex));
	temp->nottpa += 1;
	temp->lttpa = get_time();
	pthread_mutex_unlock(&(temp->philos->detex));
	msleep(temp->philos->tte);
	return (0);
}

int	sleeping_thinking(t_philo *temp, t_philos *aux)
{
	if (check_if_death_happen(temp, temp->id))
		return (1);
	printf(MAG"%ld %d is sleeping" RESET "\n", get_time() - aux->st, temp->id);
	msleep(aux->tts);
	if (check_if_death_happen(temp, temp->id))
		return (1);
	printf(GRN"%ld %d is thinking" RESET "\n", get_time() - aux->st, temp->id);
	return (0);
}
