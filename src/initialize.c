/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:17:58 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/27 19:22:46 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philos	*initialize(char **av)
{
	t_philos	*philos;

	philos = (t_philos *)malloc(sizeof(t_philos));
	if (!philos)
		exit (1);
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

void	init_mutex(t_philos *philos)
{
	int	i;

	i = 0;
	philos->eating = malloc(sizeof(pthread_mutex_t) * philos->nop);
	if (!philos->eating)
		exit (1);
	while (i < philos->nop)
	{
		pthread_mutex_init(&philos->eating[i], NULL);
		i++;
	}
	pthread_mutex_init(&philos->detex, NULL);
}

t_philo	*init_philos(t_philos *philos)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * philos->nop);
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

void	threads_create(t_philos *philos, t_philo *philo)
{
	int			i;

	i = 0;
	philos->th = (pthread_t *)malloc(sizeof(pthread_t) * philos->nop + 1);
	if (!philos->th)
		return ;
	while (i < philos->nop)
	{
		if (pthread_create(&philos->th[i], NULL, &routine, &philo[i]))
			return ;
		msleep(1);
		i++;
	}
	if (pthread_create(&philos->th[i], NULL, &s_routine, philos))
		return ;
	i = 0;
	while (i < philos->nop)
	{
		if (pthread_join(philos->th[i], NULL))
			return ;
		i++;
	}
	if (pthread_join(philos->th[i], NULL))
		return ;
}

int	one_philo(t_philos *philos)
{
	printf(Y"%ld %d has taken a fork" RESET "\n",
		get_time() - philos->st, 1);
	printf(GRN"%ld %d is thinking" RESET "\n", get_time() - philos->st, 1);
	msleep(philos->ttd * 1000);
	printf(RED"%ld %d died" RESET "\n", get_time() - philos->st, 1);
	free (philos);
	return (1);
}
