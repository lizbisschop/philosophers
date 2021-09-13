#include "philo.h"

int     join_threads(t_philos *philos, t_table *tab)
{
	int i;

	i = 0;
	while (i < philos->nb_philos)
	{
		if (pthread_join(tab->threads[i], NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_join(philos->dead_or_alive, NULL) != 0)
		return (-1);
	return (0);
}

int    destroy_mutexes(t_table *tab, int nbr)
{
	int i;

	i = 0;
	while (i < nbr)
	{
		if (pthread_mutex_destroy(&tab->forks[i]) != 0)
			return (-1);
		i++;
	}
	if (pthread_mutex_destroy(&tab->writing) != 0)
		return (-1);
	return (0);
}

int    threading(t_philos *philos, t_table *tab)
{
	int i;
	
	i = 0;
	while (i < philos->nb_philos)
	{
		if (pthread_create(&(tab->threads[i]), NULL, &eat_sleep_think, (void *)&(philos->p[i])) != 0)
			return (-1);
		i++;
	}
	if (pthread_create(&(philos->dead_or_alive), NULL, &check_dead_or_alive, (void *)(philos)) != 0)
		return (-1);
	if (philos->philo_dead == 1)
		return (-1);
	if (join_threads(philos, tab) == -1)
		return (-1);
	if (destroy_mutexes(tab, philos->nb_philos) == -1)
		return (-1);
	return (0);
}