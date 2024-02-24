/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:44:56 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/23 16:52:22 by bekhodad         ###   ########.fr       */
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

void	initialize(int ac, char **av)
{
	t_philo	*philo;

	ac++;
	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		exit (1);
	philo->nop = atoi(av[1]);
	philo->ttd = atoi(av[2]);
	philo->tte = atoi(av[3]);
	philo->tts = atoi(av[4]);
	philo->death = 0;
	philo->st = get_time();
	philo->notepme = atoi(av[5]);
	philo->eating = malloc(sizeof(pthread_mutex_t) * philo->nop);
	for (int i = 0; i < philo->nop; i++)
    {
        pthread_mutex_init(&philo->eating[i], NULL);
    }
	threads_create(&philo);
}

void	threads_create(t_philo **philo)
{
	t_philos *philos = (t_philos *)malloc(sizeof(t_philos) * (*philo)->nop);
    for (int i = 0; i < (*philo)->nop; i++)
    {
        philos[i].philo = *philo;
        philos[i].id = i;
    }
	// if ((*philo)->nop % 2)
	// 	odd_condition(philo);
	// else
		even_condition(&philos, philo);
}

void	even_condition(t_philos **philos, t_philo **philo)
{
	int			i;
	pthread_t	th[(*philo)->nop];

	i = 0;
	while (i < (*philo)->nop)
	{
		// (*philos)[i].id = i + 1;
		if (pthread_create(&th[i], NULL, &routine, &(*philos)[i]))
			exit (2);
		usleep(10);
		i++;
	}
	i = 0;
	while (i < (*philo)->nop)
	{
		if (pthread_join(th[i], NULL))
			exit (2);
		i++;
	}
}

void	*routine(void *arg)
{
	t_philos	temp;
	t_philo		*aux;
	int			j;
	long		st;

	temp = *(t_philos *)arg;
	aux = temp.philo;
	j = temp.id;
	st = aux->st;
	if (j == 0)
		routine_first(aux, j);
	else
	{
		while (1)
		{
			pthread_mutex_lock(&(*aux).eating[j]);
			printf("%ld %d has taken a fork\n", get_time() - st, j + 1);
			pthread_mutex_lock(&(*aux).eating[(j + 1) % (*aux).nop]);
			printf("%ld %d has taken a fork\n", get_time() - st, j + 1);
			printf("%ld %d is eating\n", get_time() - st, j + 1);
			usleep((*aux).tte * 1000);
			pthread_mutex_unlock(&(*aux).eating[(j + 1) % (*aux).nop]);
			pthread_mutex_unlock(&(*aux).eating[j]);
			printf("%ld %d is sleeping\n", get_time() - st, j + 1);
			usleep((*aux).tts * 1000);
			printf("%ld %d is thinking\n", get_time() - st, j + 1);
		}
	}
	return NULL;
}

void	routine_first(t_philo *temp, int j)
{
	long	st;

	st = temp->st;
	while (1)
	{
		pthread_mutex_lock(&(*temp).eating[(j + 1) % (*temp).nop]);
		printf("%ld %d has taken a fork\n", get_time() - st, j + 1);
		pthread_mutex_lock(&(*temp).eating[j]);
		printf("%ld %d has taken a fork\n", get_time() - st, j + 1);
		printf("%ld %d is eating\n", get_time() - st, j + 1);
		usleep((*temp).tte * 1000);
		pthread_mutex_unlock(&(*temp).eating[j]);
		pthread_mutex_unlock(&(*temp).eating[(j + 1) % (*temp).nop]);
		printf("%ld %d is sleeping\n", get_time() - st, j + 1);
		usleep((*temp).tts * 1000);
		printf("%ld %d is thinking\n", get_time() - st, j + 1);
	}
}

long	get_time(void)
{
    struct timeval	time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * (long)1000) + (time.tv_usec / 1000));
}

