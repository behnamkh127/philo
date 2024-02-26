/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:16:08 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/26 14:31:05 by bekhodad         ###   ########.fr       */
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
			if (source->ptr_to_philos[i].nottpa == source->notepme)
			{
				flag += 1;
				i++;
				continue;
			}
			i++;
		}
		if (flag == source->nop || source->death)
			break;
	}
	return NULL;
}
