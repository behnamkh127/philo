/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:17:58 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/24 16:28:02 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	initialize(int ac, char **av)
{
	t_philo	*philo;

	ac++;
	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		exit (1);
	philo->nop = atoi(av[1]);
	philo->ttd = (long)atoi(av[2]);
	philo->tte = (long)atoi(av[3]);
	philo->tts = (long)atoi(av[4]);
	philo->death = 0;
	philo->st = get_time();
	philo->notepme = atoi(av[5]);
	philo->eating = malloc(sizeof(pthread_mutex_t) * philo->nop);
	for (int i = 0; i < philo->nop; i++)
    {
        pthread_mutex_init(&philo->eating[i], NULL);
    }
	pthread_mutex_init(&philo->detex, NULL);
	threads_create(&philo);
}

void	threads_create(t_philo **philo)
{
	t_philos		*philos;
	t_supervisor	*supervisor;

	philos = (t_philos *)malloc(sizeof(t_philos) * (*philo)->nop);
	supervisor = (t_supervisor *)malloc(sizeof(t_supervisor));
    for (int i = 0; i < (*philo)->nop; i++)
    {
        philos[i].philo = *philo;
		philos[i].nottpa = 0;
		philos[i].died = 0;
        philos[i].id = i;
		philos[i].lttpa = get_time();
    }
	supervisor->source = philos;
	supervisor->main = *philo;
	// if ((*philo)->nop % 2)
	// 	odd_condition(philo);
	// else
		even_condition(&philos, philo, &supervisor);
}