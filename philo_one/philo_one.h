#ifndef PHILO_ONE_H
#define PHILO_ONE_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct	s_table {
	pthread_mutex_t *forks;
}				t_table;

typedef struct	s_philosopher {
	int nbr;
	int times_eaten;
	int time_die;
	int time_eat;
	int	time_sleep;
}				t_philosopher;

typedef struct	s_phil {
	int nb_philos;
	t_philosopher	*p;
}				t_phil;


int			ft_atoi(char *str);
int         threading(t_phil *phil, t_table *tab);

#endif