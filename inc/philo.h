/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bekhodad <bekhodad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:10:17 by bekhodad          #+#    #+#             */
/*   Updated: 2024/02/28 12:16:08 by bekhodad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define Y   "\x1B[33m"
#define BLU   "\x1B[34m"
#define CYN   "\x1B[36m"
#define MAG   "\x1B[35m"
#define RESET "\x1B[0m"

typedef struct s_philo	t_philo;

typedef struct s_philos
{
	int				nop;
	long			ttd;
	long			tte;
	long			tts;
	int				notepme;
	int				death;
	long			st;
	pthread_t		*th;
	pthread_mutex_t	*fork;
	pthread_mutex_t	detex;
	t_philo			*ptr_to_philo;
}	t_philos;

typedef struct s_philo
{
	int			id;
	int			nottpa;
	long		lttpa;
	int			died;
	t_philos	*philos;
}	t_philo;

//death
int			check_if_death_happen(t_philo *temp, int j);

//supervisor routine
void		*s_routine(void *arg);
int			change_feed_flag(t_philos *source, int i, int *flag);
int			change_death_flags(t_philos *source, int i);

//utilities
int			check_values(int ac, char **av);
void		free_func(t_philos *philos, t_philo *philo);
int			ft_atoi(const char *nb);
long		get_time(void);
void		msleep(int ms);

//initialize
t_philos	*initialize(char **av);
int			init_mutex(t_philos *philos);
t_philo		*init_philos(t_philos *philos);
int			threads_create(t_philos *philos, t_philo *philo);
int			one_philo(t_philos *philos);

//routine
void		*routine(void *arg);
int			fork_taking(t_philo *temp, int first_fork, int second_fork);
int			eating(t_philo *temp, int first_fork, int second_fork);
int			sleeping_thinking(t_philo *temp, t_philos *aux);
