/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:16:08 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/29 17:44:00 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(void *arg)
{
	t_philo	*temp;

	temp = (t_philo *)arg;
	select_fork(temp);
	while (1)
	{
		if (check_if_death_happen(temp, temp->id))
			break ;
		if (fork_taking(temp))
			break ;
		if (sleeping_thinking(temp, temp->philos))
			break ;
	}
	return (NULL);
}

void	select_fork(t_philo *temp)
{
	if (temp->id == 1)
	{
		temp->first_fork = temp->id;
		temp->second_fork = temp->id - 1;
	}
	else
	{
		temp->first_fork = temp->id - 1;
		temp->second_fork = temp->id % temp->philos->nop;
	}
}

int	fork_taking(t_philo *temp)
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
	pthread_mutex_lock(&temp->philos->fork[temp->first_fork]);
	printf(Y"%ld %d has taken a fork"RESET"\n",
		get_time() - temp->philos->st, temp->id);
	if (check_if_death_happen(temp, temp->id))
	{
		pthread_mutex_unlock(&temp->philos->fork[temp->first_fork]);
		return (1);
	}
	pthread_mutex_lock(&temp->philos->fork[temp->second_fork]);
	if (eating(temp))
		return (1);
	pthread_mutex_unlock(&temp->philos->fork[temp->second_fork]);
	pthread_mutex_unlock(&temp->philos->fork[temp->first_fork]);
	return (0);
}

int	eating(t_philo *temp)
{
	if (check_if_death_happen(temp, temp->id))
	{
		pthread_mutex_unlock(&temp->philos->fork[temp->second_fork]);
		pthread_mutex_unlock(&temp->philos->fork[temp->first_fork]);
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
	ft_usleep(temp->philos->tte);
	return (0);
}

int	sleeping_thinking(t_philo *temp, t_philos *aux)
{
	if (check_if_death_happen(temp, temp->id))
		return (1);
	printf(MAG"%ld %d is sleeping" RESET "\n", get_time() - aux->st, temp->id);
	ft_usleep(aux->tts);
	if (check_if_death_happen(temp, temp->id))
		return (1);
	printf(GRN"%ld %d is thinking" RESET "\n", get_time() - aux->st, temp->id);
	return (0);
}
