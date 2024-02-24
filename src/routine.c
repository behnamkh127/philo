/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:16:08 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/24 16:40:02 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(void *arg)
{
	t_philos	temp;
	t_philo		*aux;
	int			j;
	long		st;

	temp = *(t_philos *)arg;
	aux = temp.philo;
	j = temp.id;
	st = aux->st;
	if (j == 0)
		routine_first(temp, aux, j);
	else
	{
		while (1)
		{
			pthread_mutex_lock(&aux->detex);
			if ((*aux).death == 1)
			{
				if (temp.died)
					printf("%ld %d died\n", get_time() - st, j + 1);
				pthread_mutex_unlock(&(*aux).detex);
				break;
			}
			pthread_mutex_unlock(&aux->detex);
			if (temp.nottpa == (*aux).notepme)
				break;
			pthread_mutex_lock(&(*aux).eating[j]);
			printf("%ld %d has taken a fork\n", get_time() - st, j + 1);
			pthread_mutex_lock(&(*aux).eating[(j + 1) % (*aux).nop]);
			printf("%ld %d has taken a fork\n", get_time() - st, j + 1);
			printf("%ld %d is eating\n", get_time() - st, j + 1);
			temp.nottpa += 1;
			temp.lttpa = get_time();
			usleep((*aux).tte * 1000);
			pthread_mutex_unlock(&(*aux).eating[(j + 1) % (*aux).nop]);
			pthread_mutex_unlock(&(*aux).eating[j]);
			printf("%ld %d is sleeping\n", get_time() - st, j + 1);
			usleep((*aux).tts * 1000);
			printf("%ld %d is thinking\n", get_time() - st, j + 1);
		}
	}
	return NULL;
}

void	routine_first(t_philos temp, t_philo *aux, int j)
{
	long	st;

	st = aux->st;
	while (1)
	{
		if (temp.nottpa == (*aux).notepme)
			break;
		pthread_mutex_lock(&(*aux).detex);
		if ((*aux).death == 1)
		{
			if (temp.died)
				printf("%ld %d died\n", get_time() - st, j + 1);
			pthread_mutex_unlock(&(*aux).detex);
			break;
		}
		pthread_mutex_unlock(&(*aux).detex);
		pthread_mutex_lock(&(*aux).eating[(j + 1) % (*aux).nop]);
		printf("%ld %d has taken a fork\n", get_time() - st, j + 1);
		pthread_mutex_lock(&(*aux).eating[j]);
		printf("%ld %d has taken a fork\n", get_time() - st, j + 1);
		printf("%ld %d is eating\n", get_time() - st, j + 1);
		temp.nottpa += 1;
		usleep((*aux).tte * 1000);
		pthread_mutex_unlock(&(*aux).eating[j]);
		pthread_mutex_unlock(&(*aux).eating[(j + 1) % (*aux).nop]);
		printf("%ld %d is sleeping\n", get_time() - st, j + 1);
		usleep((*aux).tts * 1000);
		printf("%ld %d is thinking\n", get_time() - st, j + 1);
	}
}

void	*s_routine(void *arg)
{
	t_supervisor	temp;
	int				i;
	int				flag;
	
	temp = *(t_supervisor *)arg;
	flag = 0;
	while (1)
	{
		i = 0;
		while (i < temp.main->nop)
		{
			printf("hereeeee\n");
			if (temp.source[i].nottpa == temp.main->notepme)
			{
				flag += 1;
				i++;
				continue;
			}
			pthread_mutex_lock(&temp.main->detex);
			if ((get_time() - temp.source[i].lttpa) > temp.main->ttd)
			{
				temp.source->died = 1;
				temp.main->death = 1;
				pthread_mutex_unlock(&temp.main->detex);
				break;
			}
			pthread_mutex_unlock(&temp.main->detex);
			i++;
		}
		if (flag == temp.main->nop || temp.main->death)
			break;
	}
	return NULL;
}
