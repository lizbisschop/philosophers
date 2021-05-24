#include "philo_one.h"

int         threading(t_phil *phil, t_table *tab)
{
	int i;

	i = 0;

	while (i < phil->nb_philos)
	{
		if (pthread_create(&(tab->threads[i]), NULL, &eat_sleep_think, (void *)&(phil->p[i])) != 0)
			return (-1);
		i++;

	}
	// (void)phil;
	// (void)tab;
	return (0);
}