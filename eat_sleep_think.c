#include "philo.h"

int	eat(t_philosopher *phil)
{
	phil->is_eating = 1;
	phil->times_eaten++;
	print_stuff(phil, "is eating");
	// printf("amount of times eaten = %d\n", phil->times_eaten);
	phil->last_time_eaten = get_time(phil->tab);
	better_sleep(phil->time_eat);
	phil->is_eating = 0;
	if (pthread_mutex_unlock(&phil->tab->forks[phil->hold_r - 1]) != 0)
	{
		phil->function_fail = 1;
		return (-1);
	}
	if (pthread_mutex_unlock(&phil->tab->forks[phil->hold_l - 1]) != 0)
	{
		phil->function_fail = 1;
		return (-1);
	}
	return (0);
}

int		get_forks(t_philosopher *phil)
{
	if (pthread_mutex_lock(&phil->tab->forks[phil->hold_r - 1]) != 0)
	{
		phil->function_fail = 1;
		return (-1);
	}
	// if (phil->nbr % 2 == 0)
	// 	pthread_mutex_lock(&phil->tab->forks[phil->hold_r - 1]);
	// else
	// 	pthread_mutex_lock(&phil->tab->forks[phil->hold_l - 1]);
	if (phil->dead_philosopher == 1)
		return (1);
	print_stuff(phil, "has taken a fork");
	// printf("forks are: right: %d left %d\n", phil->hold_r, phil->hold_l);
	// printf("%d | %d\n", phil->hold_r - 1, phil->hold_l - 1);
	// printf("Cant's go further then thisss\n");
	if (pthread_mutex_lock(&phil->tab->forks[phil->hold_l - 1]) != 0)
	{
		phil->function_fail = 1;
		return (-1);
	}
	// if (phil->nbr % 2 == 0)
	// 	pthread_mutex_lock(&phil->tab->forks[phil->hold_l - 1]);
	// else
		// pthread_mutex_lock(&phil->tab->forks[phil->hold_r - 1]);
	if (phil->dead_philosopher == 1)
		return (1);
	print_stuff(phil, "has taken a fork");
	return (0);
}

void	*eat_sleep_think(void *p)
{
	t_philosopher *phil;
	phil = (t_philosopher *)p;
	// printf("philo number = %d\n", phil->nbr);
	if (phil->nbr % 2 == 0)
		usleep(175);
	while (phil->dead_philosopher != 1 && !(phil->times_eaten == phil->times_to_eat && phil->arg_5 == 1))
	{
		// printf(" Status of philo = %d\n", phil->dead_philosopher);
		if (get_forks(phil))
			break ;
		if (eat(phil) != 0)
			phil->function_fail = 1;
		if (phil->dead_philosopher == 1 || (phil->arg_5 == 1 && phil->times_eaten == phil->times_to_eat))
		{
			// if (phil->times_eaten == phil->times_to_eat)
			// 	printf("EAT LIMIT HAS BEEN MADE! %d %d \n", phil->times_eaten, phil->times_to_eat);
			// else
			// {
			// 		printf("WHY YOU DEAD???\n");
			// }
			break ;
		}
		print_stuff(phil, "is sleeping");
		better_sleep(phil->time_sleep);
		if (phil->dead_philosopher == 1)
			break ;
		print_stuff(phil, "is thinking");
		// printf("this is where I hang\n");
	}
	return (NULL);
}
