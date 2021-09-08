#include "philo.h"

int			join_threads(t_phil *phil, t_table *tab)
{
	int i;

	i = 0;
	while (i < phil->nb_philos)
	{
		if (pthread_join(tab->threads[i], NULL) != 0)
			return (-1);
		i++;
	}

	if (pthread_join(phil->dead_or_alive, NULL) != 0)
		return (-1);
	return (0);
}

int			destroy_mutexes(t_table *tab, int nbr)
{
	int i;

	i = 0;
	printf("I am being destroyed\n");
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

int         threading(t_phil *phil, t_table *tab)
{
	int i;

	i = 0;

	while (i < phil->nb_philos)
	{
		if (pthread_create(&(tab->threads[i]), NULL, &eat_sleep_think, (void *)&(phil->p[i])) != 0)
			return (-1);
		// eat_sleep_think((void*)&phil->p[i]);
		i++;
	}
	// printf("total number = %d\n", phil->p[0].total_nbr);
	if (pthread_create(&(phil->dead_or_alive), NULL, &check_dead_or_alive, (void *)(phil)) != 0)
		return (-1);
	if (phil->philo_dead == 1)
		return (-1);
	if (join_threads(phil, tab) == -1)
		return (-1);
	printf("hello\n");
	if (destroy_mutexes(tab, phil->nb_philos) == -1)
		return (-1);
	

	// (void)phil;
	(void)tab;
	return (0);
}