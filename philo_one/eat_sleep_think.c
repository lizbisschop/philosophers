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
   pthread_mutex_lock(&phil->tab->forks[phil->hold_l - 1]);
   print_stuff(phil, "has taken fork");
   return (0);

}

void    *eat_sleep_think(void *p)
{
	t_philosopher *phil;

	phil = (t_philosopher *)p;
	if (phil->nbr % 2 == 0)
		usleep(200);
	while (!(phil->times_eaten == phil->times_to_eat && phil->arg_5 == 1))
	{
		if (get_forks(phil))
			break ;
		eat(phil);
		print_stuff(phil, "is sleeping");
		usleep(phil->time_sleep * 1000);
		printf("yellow\n");
	}
	return (p);
}