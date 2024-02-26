/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:10:17 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/26 17:23:25 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define CYN   "\x1B[36m"
#define MAG   "\x1B[35m"
#define RESET "\x1B[0m"

typedef struct s_philos t_philos;

typedef struct s_philo
{
	int		nop;
	long	ttd;
	long	tte;
	long	tts;
	int		notepme;
	int		death;
	long	st;
	pthread_mutex_t *eating;
	pthread_mutex_t	detex;
	t_philos	*ptr_to_philos;
}	t_philo;

typedef struct s_philos
{
	int		id;
	int		nottpa;
	long	lttpa;
	int		died;
	t_philo	*philo;
}	t_philos;

// typedef struct s_supervisor
// {
// 	t_philos	**source;
// 	// t_philo		*main;
// }	t_supervisor;


void	initialize(int ac, char **av);
void	even_condition(t_philos *philos, t_philo *philo);
void	threads_create(t_philo *philo);
void	*routine(void *arg);
long	get_time(void);
void	*s_routine(void *arg);
int		check_if_death_happen(t_philos *temp, t_philo *aux, int j);
int		eating(t_philos *temp, t_philo *aux, int first_fork, int second_fork);
int		sleeping_thinking(t_philos *temp, t_philo *aux);
int		ft_atoi(const char *nb);