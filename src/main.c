/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:44:56 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/26 17:26:14 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/philo.h"

int	main(int ac, char **av)
{
	if (ac < 5)
	{
		printf("Number of arguments less than required\n");
		return (1);
	}
	if (ac > 6)
	{
		printf("Number of arguments more than need\n");
		return (1);
	}
	else
		initialize(ac, av);
	return (0);
}



void	even_condition(t_philos *philos, t_philo *philo)
{
	int			i;
	pthread_t	th[philo->nop + 1];

	i = 0;
	while (i < philo->nop)
	{
		if (pthread_create(&th[i], NULL, &routine, &philos[i]))
			exit (2);
		usleep(10);
		i++;
	}
	if (pthread_create(&th[i], NULL, &s_routine, philo))
		exit (2);
	i = 0;
	while (i < philo->nop)
	{
		if (pthread_join(th[i], NULL))
			exit (2);
		i++;
	}
	if (pthread_join(th[i], NULL))
		exit (2);
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
