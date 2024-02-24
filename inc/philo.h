/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:10:17 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/23 16:39:05 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_philo
{
	int	nop;
	int	ttd;
	int	tte;
	int	tts;
	int	notepme;
	int	death;
	long	st;
	pthread_mutex_t *eating;
}	t_philo;

typedef struct s_philos
{
	int	id;
	t_philo	*philo;
}	t_philos;

void	initialize(int ac, char **av);
void	even_condition(t_philos **philos, t_philo **philo);
void	threads_create(t_philo **philo);
void	odd_condition(t_philo *philo);
void	*routine(void *arg);
void	routine_first(t_philo *temp, int j);
long	get_time(void);