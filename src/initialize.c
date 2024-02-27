/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:17:58 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/27 13:49:07 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philo	*initialize(char **av)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		exit (1);
	philo->nop = ft_atoi(av[1]);
	philo->ttd = (long)ft_atoi(av[2]);
	philo->tte = (long)ft_atoi(av[3]);
	philo->tts = (long)ft_atoi(av[4]);
	philo->death = 0;
	philo->st = get_time();
	if (av[5])
		philo->notepme = atoi(av[5]);
	else
		philo->notepme = -1;
	if (check_values(philo))
	{
		free (philo);
		philo = NULL;
	}
	return (philo);
}

int	check_values(t_philo *philo)
{
	if (philo->nop <= 0 || philo->ttd < 0 || philo->tte <= 0 || philo->tts < 0)
	{
		free (philo);
		return (1);
	}
	if (philo->nop == 1)
	{
		printf(YEL"%ld %d has taken a fork" RESET "\n",
			get_time() - philo->st, 1);
		printf(GRN"%ld %d is thinking" RESET "\n", get_time() - philo->st, 1);
		usleep(philo->ttd * 1000);
		printf(RED"%ld %d died" RESET "\n", get_time() - philo->st, 1);
		free (philo);
		return (1);
	}
	return (0);
}

void	init_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	philo->eating = malloc(sizeof(pthread_mutex_t) * philo->nop);
	if (!philo->eating)
		exit (1);
	while (i < philo->nop)
	{
		pthread_mutex_init(&philo->eating[i], NULL);
		i++;
	}
	pthread_mutex_init(&philo->detex, NULL);
}

t_philos	*init_philos(t_philo *philo)
{
	t_philos	*philos;
	int			i;

	i = 0;
	philos = (t_philos *)malloc(sizeof(t_philos) * philo->nop);
	while (i < philo->nop)
	{
		philos[i].philo = philo;
		philos[i].nottpa = 0;
		philos[i].died = 0;
		philos[i].id = i + 1;
		philos[i].lttpa = get_time();
		i++;
	}
	philo->ptr_to_philos = philos;
	return (philos);
}

void	threads_create(t_philo *philo, t_philos *philos)
{
	int			i;

	i = 0;
	philo->th = (pthread_t *)malloc(sizeof(pthread_t) * philo->nop + 1);
	if (!philo->th)
		return ;
	while (i < philo->nop)
	{
		if (pthread_create(&philo->th[i], NULL, &routine, &philos[i]))
			return ;
		usleep(10);
		i++;
	}
	if (pthread_create(&philo->th[i], NULL, &s_routine, philo))
		return ;
	i = 0;
	while (i < philo->nop)
	{
		if (pthread_join(philo->th[i], NULL))
			return ;
		i++;
	}
	if (pthread_join(philo->th[i], NULL))
		return ;
}
