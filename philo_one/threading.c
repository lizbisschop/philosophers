#include "philo_one.h"

int         threading(t_phil *phil, t_table *tab)
{
	tab->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * phil->nb_philos);
	if (!tab->forks)
		return (-1);
	return (0);
}