#include "philo_one.h"

void		join_threads(t_phil *phil, t_table *tab)
{
	int i;

	i = 0;
	while (i < phil->nb_philos)
	{
		pthread_join(tab->threads[i], NULL);
	}
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
	join_threads(phil, tab);
	// (void)phil;
	(void)tab;
	return (0);
}