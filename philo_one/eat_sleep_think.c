#include "philo_one.h"

void    eat(t_philosopher *phil)
{
	print_stuff(phil, "is eating");
	pthread_mutex_unlock(&phil->tab->forks[phil->hold_r - 1]);
	pthread_mutex_unlock(&phil->tab->forks[phil->hold_l - 1]);
	phil->times_eaten++;
}

int    get_forks(t_philosopher *phil)
{
	pthread_mutex_lock(&phil->tab->forks[phil->hold_r - 1]);
	print_stuff(phil, "has taken a fork");
	printf("%d | %d\n", phil->hold_r - 1, phil->hold_l - 1);
	pthread_mutex_lock(&phil->tab->forks[phil->hold_l - 1]);
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
	while (!(phil->times_eaten == phil->times_to_eat && phil->arg_5 == 1))
	{
		if (get_forks(phil))
			break ;
		eat(phil);
		print_stuff(phil, "is sleeping");
		usleep(phil->time_sleep * 1000);
		i++;
	}
	printf("out of the loop\n");
	return (p);
}