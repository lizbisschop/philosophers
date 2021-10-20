#include "philo.h"

int	dying(t_philos *philos, int i)
{
	long long int	now;

	now = get_time(philos->p[i].tab);
	if (now - philos->p[i].last_time_eaten > philos->p[i].time_die
		&& philos->p[i].is_eating == 0)
	{
		philos->philo_dead = 1;
		philos->p[i].dead_philosopher = 1;
		printf("Now - last time eaten %lld philo %d time to die = %d\n", now - philos->p[i].last_time_eaten, philos->p[i].nbr, philos->p[i].time_die);
		print_stuff(&philos->p[i], "died");
		return (1);
	}
	return (0);
}

void	*check_dead_or_alive(void *philosophers)
{
	t_philos	*philos;
	int			i;

	philos = (t_philos *)philosophers;
	while (1)
	{
		i = 0;
		while (i < philos->p[0].total_nbr)
		{
			if (philos->p[i].arg_5 == 1 && philos->p[i].times_eaten
				== philos->p[i].times_to_eat)
				break ;
			if (dying(philos, i))
				break ;
			i++;
		}
		if (philos->p[i].arg_5 == 1 && philos->p[i].times_eaten
			== philos->p[i].times_to_eat)
			break ;
		if (philos->p[i].dead_philosopher == 1)
			break ;
	}
	if (philos->p[i].arg_5 && philos->p[i].times_eaten
		== philos->p[i].times_to_eat && philos->philo_dead != 1)
		return (0);
	i = 0;
	while (i < philos->p[0].total_nbr)
	{
		philos->p[i].dead_philosopher = philos->philo_dead;
		i++;
	}
	return (0);
}
