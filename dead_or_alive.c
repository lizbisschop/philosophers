#include "philo.h"

int dying(t_philos *philos, int i)
{
	long long int now;

	now = get_time(philos->p[i].tab);
	// printf("timeee = %lli | %lli\n", now, philos->p[i].last_time_eaten);
	if (now - philos->p[i].last_time_eaten > philos->p[i].time_die)
	{
		printf("Now - last time eaten %lld philo %d time to die = %d\n", now - philos->p[i].last_time_eaten, philos->p[i].nbr, philos->p[i].time_die);
		print_stuff(&philos->p[i], "Died");
		philos->philo_dead = 1;
		philos->p[i].dead_philosopher = 1;
		return (1);
	}
	return (0);
}

void		*check_dead_or_alive(void *philosophers)
{
	t_philos *philos;
	int i;
	
	philos = (t_philos *)philosophers;	
	// printf("total number of pihlos = %d\n", philos->p[0].total_nbr);
	while (1)
	{
		i = 0;
		while (i < philos->p[0].total_nbr)
		{
			// printf("PHILO_NUMBER = %d\n", philos->p[i].nbr);
			if (dying(philos, i))
				break ;
			i++;
		}
		if (philos->p[i].dead_philosopher == 1)
			break ;
	}
	i = 0;
	while (i < philos->p[0].total_nbr)
	{
		philos->p[i].dead_philosopher = philos->philo_dead;
		i++;
	}
	// (void)philosophers;
	return (0);
}