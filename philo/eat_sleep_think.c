#include "philo.h"

void    eat(t_philosopher *phil)
{
	phil->last_time_eaten = get_time(phil->tab);
	print_stuff(phil, "is eating");

	pthread_mutex_unlock(&phil->tab->forks[phil->hold_r - 1]);
	pthread_mutex_unlock(&phil->tab->forks[phil->hold_l - 1]);
	phil->times_eaten++;
}

int    get_forks(t_philosopher *phil)
{
	pthread_mutex_lock(&phil->tab->forks[phil->hold_r - 1]);
	if (phil->dead_philosopher == 1)
		return (1);
	print_stuff(phil, "has taken a fork");
	// printf("%d | %d\n", phil->hold_r - 1, phil->hold_l - 1);
	// printf("Cant's go further then thisss\n");
	pthread_mutex_lock(&phil->tab->forks[phil->hold_l - 1]);
	if (phil->dead_philosopher == 1)
		return (1);
	print_stuff(phil, "has taken fork");
	return (0);

}

void    *eat_sleep_think(void *p)
{
	t_philosopher *phil;
	int i;

	i = 0;
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
			break ;
		print_stuff(phil, "is sleeping");
		usleep(phil->time_sleep * 1000);
		i++;
	}
	printf("out of the loop\n");
	return (p);
}