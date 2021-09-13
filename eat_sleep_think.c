#include "philo.h"

void    eat(t_philosopher *phil)
{
	phil->last_time_eaten = get_time(phil->tab);
	print_stuff(phil, "is eating");
	phil->times_eaten++;
	usleep(phil->time_eat * 1000);
	pthread_mutex_unlock(&phil->tab->forks[phil->hold_r]);
	pthread_mutex_unlock(&phil->tab->forks[phil->hold_l]);
}

int    get_forks(t_philosopher *phil)
{
	pthread_mutex_lock(&phil->tab->forks[phil->hold_r]);
	if (phil->dead_philosopher == 1)
		return (1);
	print_stuff(phil, "has taken a fork");
	// printf("%d | %d\n", phil->hold_r - 1, phil->hold_l - 1);
	// printf("Cant's go further then thisss\n");
	pthread_mutex_lock(&phil->tab->forks[phil->hold_l]);
	if (phil->dead_philosopher == 1)
		return (1);
	print_stuff(phil, "has taken a fork");
	return (0);
}

void    *eat_sleep_think(void *p)
{
	t_philosopher *phil;
	phil = (t_philosopher *)p;
	// printf("philo number = %d\n", phil->nbr);
	// if (phil->nbr % 2 == 0)
	// 	usleep(175);
	while (phil->dead_philosopher != 1 && !(phil->times_eaten == phil->times_to_eat && phil->arg_5 == 1))
	{
		// printf(" Status of philo = %d\n", phil->dead_philosopher);
		if (get_forks(phil))
			break ;
		eat(phil);
		if (phil->dead_philosopher == 1 || (phil->arg_5 == 1 && phil->times_eaten == phil->times_to_eat))
		{
			break ;
		}
		print_stuff(phil, "is sleeping");
		usleep(phil->time_sleep * 1000);
		if (phil->dead_philosopher == 1)
			break ;
		print_stuff(phil, "is thinking");
	}
	return (NULL);
}