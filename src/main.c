/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:44:56 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/24 15:18:58 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/philo.h"

int	main(int ac, char **av)
{
	// if (ac == 1)
	// 	perror ("Number of arguments less than required\n");
	// if (ac > 5)
	// 	perror ("Number of arguments more than need\n");
	// else
		initialize(ac, av);
	
}



void	even_condition(t_philos **philos, t_philo **philo, t_supervisor **supervisor)
{
	int			i;
	pthread_t	th[(*philo)->nop + 1];

	i = 0;
	while (i < (*philo)->nop)
	{
		if (pthread_create(&th[i], NULL, &routine, &(*philos)[i]))
			exit (2);
		usleep(10);
		i++;
	}
	if (pthread_create(&th[i], NULL, &s_routine, &(*supervisor)))
		exit (2);
	i = 0;
	while (i < (*philo)->nop)
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
