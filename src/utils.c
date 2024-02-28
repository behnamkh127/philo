/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:42:01 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/28 11:21:27 by bekhodad         ###   ########.fr       */
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

void	msleep(int ms)
{
	struct timespec	req;
	struct timespec	rem;

	if (ms > 999)
	{
		req.tv_sec = (int)(ms / 1000);
		req.tv_nsec = (ms - ((long)req.tv_sec * 1000)) * 1000000;
	}
	else
	{
		req.tv_sec = 0;
		req.tv_nsec = ms * 1000000;
	}
	while (nanosleep(&req, &rem))
	{
		req = rem;
	}
}
