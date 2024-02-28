/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:42:01 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/28 18:35:13 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_values(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf(RED"Wrong Number of arguments " RESET "\n");
		return (1);
	}
	if (ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60)
	{
		printf(RED"Time of everything should be more than 60" RESET "\n");
		return (1);
	}
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[1]) > 200)
	{
		printf(RED"Wrong Number of philos " RESET "\n");
		return (1);
	}
	return (0);
}

void	free_func(t_philos *philos, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philos->nop)
		pthread_mutex_destroy(&philos->fork[i++]);
	pthread_mutex_destroy(&philos->detex);
	free(philos->th);
	free(philo);
	free(philos->fork);
	free(philos);
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

long	ft_usleep(int m_sec)
{
	int	before;
	int	after;

	before = get_time();
	after = before;
	while (after - before < m_sec)
	{
		usleep(100);
		after = get_time();
	}
	return (0);
}
