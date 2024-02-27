/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_routine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:55:49 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/27 19:18:07 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*s_routine(void *arg)
{
	t_philos	*source;
	int			i;
	int			feed_flag;

	source = (t_philos *)arg;
	feed_flag = 0;
	while (1)
	{
		i = 0;
		while (i < source->nop)
		{
			if (change_death_flags(source, i))
				break ;
			if (change_feed_flag(source, i, &feed_flag))
				continue ;
			i++;
		}
		if (feed_flag == source->nop || source->death)
			break ;
	}
	return (NULL);
}

int	change_feed_flag(t_philos *source, int i, int *feed_flag)
{
	pthread_mutex_lock(&(source->detex));
	if (source->ptr_to_philo[i].nottpa == source->notepme)
	{
		feed_flag += 1;
		i++;
		pthread_mutex_unlock(&(source->detex));
		return (1);
	}
	pthread_mutex_unlock(&(source->detex));
	return (0);
}

int	change_death_flags(t_philos *source, int i)
{
	pthread_mutex_lock(&(source->detex));
	if ((get_time() - source->ptr_to_philo[i].lttpa) > source->ttd)
	{
		source->ptr_to_philo[i].died = 1;
		source->death = 1;
		pthread_mutex_unlock(&(source->detex));
		return (1);
	}
	pthread_mutex_unlock(&(source->detex));
	return (0);
}
