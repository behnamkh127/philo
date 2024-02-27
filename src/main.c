/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:44:56 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/27 14:01:54 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/philo.h"

int	main(int ac, char **av)
{
	t_philo			*philo;
	t_philos		*philos;

	if (ac < 5 || ac > 6)
	{
		printf("Wrong Number of arguments\n");
		return (1);
	}
	philo = initialize(av);
	if (!philo)
		return (1);
	init_mutex(philo);
	philos = init_philos(philo);
	threads_create(philo, philos);
	free_func(philo, philos);
	return (0);
}

#include <stdio.h> // Add include statement for printf
#include <stdlib.h> // Add include statement for free

void	free_func(t_philo *philo, t_philos *philos)
{
	int	i;
	
	i = 0;
	while (i < philo->nop)
		pthread_mutex_destroy(&philo->eating[i++]);
	pthread_mutex_destroy(&philo->detex);
	free(philo->th);
	free(philos);
	free(philo->eating);
	free(philo);
}

long	get_time(void)
{
    struct timeval	time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * (long)1000) + (time.tv_usec / 1000));
}

int	ft_atoi(const char *nb)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (*nb == '\t' || *nb == '\n' || *nb == '\v' || *nb == '\f'
		|| *nb == '\r' || *nb == ' ')
		nb++;
	if (*nb == '-')
	{
		sign = -1;
		nb++;
	}
	else if (*nb == '+')
		nb++;
	while (*nb >= '0' && *nb <= '9')
	{
		result = result * 10 + (*nb - '0');
		nb++;
	}
	return (result * sign);
}
