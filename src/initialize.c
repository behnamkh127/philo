/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:17:58 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/28 11:58:18 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philos	*initialize(char **av)
{
	t_philos	*philos;

	philos = (t_philos *)malloc(sizeof(t_philos));
	if (!philos)
		return (NULL);
	philos->nop = ft_atoi(av[1]);
	philos->ttd = (long)ft_atoi(av[2]);
	philos->tte = (long)ft_atoi(av[3]);
	philos->tts = (long)ft_atoi(av[4]);
	philos->death = 0;
	philos->st = get_time();
	if (av[5])
		philos->notepme = atoi(av[5]);
	else
		philos->notepme = -1;
	return (philos);
}

int	init_mutex(t_philos *philos)
{
	int	i;

	i = 0;
	philos->fork = malloc(sizeof(pthread_mutex_t) * philos->nop);
	if (!philos->fork)
	{
		free (philos);
		return (1);
	}
	while (i < philos->nop)
	{
		pthread_mutex_init(&philos->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&philos->detex, NULL);
	return (0);
}

t_philo	*init_philos(t_philos *philos)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * philos->nop);
	if (!philo)
	{
		free_func(philos, NULL);
		return (NULL);
	}
	while (i < philos->nop)
	{
		philo[i].philos = philos;
		philo[i].nottpa = 0;
		philo[i].died = 0;
		philo[i].id = i + 1;
		philo[i].lttpa = get_time();
		i++;
	}
	philos->ptr_to_philo = philo;
	return (philo);
}

int	threads_create(t_philos *philos, t_philo *philo)
{
	int			i;

	i = 0;
	philos->th = (pthread_t *)malloc(sizeof(pthread_t) * (philos->nop + 1));
	if (!philos->th)
		return (1);
	while (i < philos->nop)
	{
		if (pthread_create(&philos->th[i], NULL, &routine, &philo[i]))
			return (1);
		msleep(1);
		i++;
	}
	if (pthread_create(&philos->th[i], NULL, &s_routine, philos))
		return (1);
	i = 0;
	while (i < philos->nop)
	{
		if (pthread_join(philos->th[i], NULL))
			return (1);
		i++;
	}
	if (pthread_join(philos->th[i], NULL))
		return (1);
	return (0);
}

int	one_philo(t_philos *philos)
{
	printf(Y"%ld %d has taken a fork" RESET "\n",
		get_time() - philos->st, 1);
	printf(GRN"%ld %d is thinking" RESET "\n", get_time() - philos->st, 1);
	msleep(philos->ttd);
	printf(RED"%ld %d died" RESET "\n", get_time() - philos->st, 1);
	free (philos);
	return (1);
}
