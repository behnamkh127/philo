/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:10:17 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/24 16:27:54 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_philo
{
	int		nop;
	long	ttd;
	long	tte;
	long	tts;
	int		notepme;
	int		death;
	long	st;
	pthread_mutex_t *eating;
	pthread_mutex_t	detex;
}	t_philo;

typedef struct s_philos
{
	int		id;
	int		nottpa;
	long	lttpa;
	int		died;
	t_philo	*philo;
}	t_philos;

typedef struct s_supervisor
{
	t_philos	*source;
	t_philo		*main;
}	t_supervisor;


void	initialize(int ac, char **av);
void	even_condition(t_philos **philos, t_philo **philo, t_supervisor **supervisor);
void	threads_create(t_philo **philo);
void	odd_condition(t_philo *philo);
void	*routine(void *arg);
void	routine_first(t_philos temp, t_philo *aux, int j);
long	get_time(void);
void	*s_routine(void *arg);