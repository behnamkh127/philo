/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:16:08 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/27 14:46:01 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(void *arg)
{
	t_philos	*temp;
	int		first_fork;
	int		second_fork;
	
	temp = (t_philos *)arg;
	if (temp->id == 1)
	{
		first_fork = temp->id;
		second_fork = temp->id - 1;
	}
	else
	{
		first_fork = temp->id - 1;
		second_fork = temp->id % temp->philo->nop;	
	}
	while (1)
	{
		if (check_if_death_happen(temp, temp->philo, temp->id))
			break ;
		if (eating(temp, temp->philo, first_fork, second_fork))
			break;
		if (sleeping_thinking(temp, temp->philo))
			break;
	}
	return NULL;
}


void	*s_routine(void *arg)
{
	t_philo		*source;
	int				i;
	int				flag;
	
	source = (t_philo *)arg;
	flag = 0;
	while (1)
	{
		i = 0;
		while (i < source->nop)
		{
			pthread_mutex_lock(&(source->detex));
			if ((get_time() - source->ptr_to_philos[i].lttpa) > source->ttd)
			{
				source->ptr_to_philos[i].died = 1;
				source->death= 1;
				pthread_mutex_unlock(&(source->detex));
				break;
			}
			pthread_mutex_unlock(&(source->detex));
			pthread_mutex_lock(&(source->detex));
			if (source->ptr_to_philos[i].nottpa == source->notepme)
			{
				flag += 1;
				i++;
				pthread_mutex_unlock(&(source->detex));
				continue;
			}
			pthread_mutex_unlock(&(source->detex));
			i++;
		}
		if (flag == source->nop || source->death)
			break;
	}
	return NULL;
}

int	eating(t_philos *temp, t_philo *aux, int first_fork, int second_fork)
{
	if (check_if_death_happen(temp, temp->philo, temp->id))
		return (1) ;
	pthread_mutex_lock(&(aux->detex));
	if (temp->nottpa == temp->philo->notepme)
	{
		pthread_mutex_unlock(&(aux->detex));
		return (1);
	}
	pthread_mutex_unlock(&(aux->detex));
	pthread_mutex_lock(&aux->eating[first_fork]);
	printf(YEL"%ld %d has taken a fork" RESET "\n", get_time() - aux->st, temp->id);
	pthread_mutex_lock(&aux->eating[second_fork]);
	printf(YEL"%ld %d has taken a fork" RESET "\n", get_time() - aux->st, temp->id);
	printf(BLU"%ld %d is eating" RESET "\n", get_time() - aux->st, temp->id);
	pthread_mutex_lock(&(aux->detex));
	temp->nottpa += 1;
	temp->lttpa = get_time();
	pthread_mutex_unlock(&(aux->detex));
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