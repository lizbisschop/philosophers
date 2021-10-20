#include "philo.h"

int	join_threads(t_philos *philos, t_table *tab)
{
	int	i;

	i = 0;
	while (i < philos->nb_philos)
	{
		if (pthread_join(tab->threads[i], NULL) != 0)
		{
			philos->function_fail = 1;
			return (-1);
		}
		i++;
	}
	if (pthread_join(philos->dead_or_alive, NULL) != 0)
	{
		philos->function_fail = 1;
		return (-1);
	}
	return (0);
}

int	destroy_mutexes(t_table *tab, int nbr, t_philos *philos)
{
	int	i;
	int	ret;

	i = 0;
	while (i < nbr)
	{
		if (tab->locked_fork[i] == 1)
			pthread_mutex_unlock(&tab->forks[i]);
		ret = pthread_mutex_destroy(&tab->forks[i]);
		if (ret != 0)
		{
			printf("%d destroy mutex failed %s\n", ret, strerror(ret));
			return (-1);
		}
		i++;
	}
	if (pthread_mutex_destroy(&tab->writing) != 0)
	{
		printf("destroy mutex failed\n");
		return (-1);
	}
	return (0);
}

void	*print_time(void *philos)
{
	t_philos	 	*phils;
	int				i;
	long long int	time;

	time = get_time(NULL);
	i = 0;
	phils = philos;
	while (1)
	{
		usleep(300000);
		while (i < phils->nb_philos)
			i++;
		i = 0;
		if (phils->philo_dead == 1)
			break ;
	}
	return (NULL);
}

int    threading(t_philos *philos, t_table *tab)
{
	int i;
	
	i = 0;
	while (i < philos->nb_philos)
	{
		if (pthread_create(&(tab->threads[i]), NULL, &eat_sleep_think, (void *)&(philos->p[i])) != 0)
		{
			philos->function_fail = 1;
			return (-1);
		}
		if (philos->p[i].function_fail == 1)
		{
			philos->function_fail = 1;	
			return (-1);
		}
		i++;
	}
	if (pthread_create(&(philos->dead_or_alive), NULL, &check_dead_or_alive, (void *)(philos)) != 0)
	{
		philos->function_fail = 1;
		return (-1);
	}
	pthread_t 	time_check;
	if (pthread_create(&(time_check), NULL, &print_time, (void *)(philos)) != 0)
	{
		philos->function_fail = 1;
		return (-1);
	}
	// if (philos->philo_dead == 1)
	// 	return (-1);
	if (join_threads(philos, tab) == -1)
	{
		philos->function_fail = 1;
		return (-1);
	}
	// if (philos->p[0].times_eaten == philos->p[0].times_to_eat)
	// 	printf("EAT LIMIT HAS BEEN MADE SCOND CHECKIE!!! %d %d \n", philos->p[0].times_eaten, philos->p[0].times_to_eat);
	// else
	// {
	// 	printf("WHY YOU DEAD MOTHA FOCKAA??  %d %d \n", philos->p[0].times_eaten, philos->p[0].times_to_eat);
	// }
	if (destroy_mutexes(tab, philos->nb_philos, philos) == -1)
	{
		philos->function_fail = 1;
		return (-1);
	}
	return (0);
}