#include "philo.h"

int	eat(t_philosopher *phil)
{
	phil->is_eating = 1;
	phil->times_eaten++;
	print_stuff(phil, "is eating");
	phil->last_time_eaten = get_time(phil->tab);
	better_sleep(phil->time_eat);
	phil->is_eating = 0;
	if (pthread_mutex_unlock(&phil->tab->forks[phil->hold_r - 1]) != 0)
	{
		phil->function_fail = 1;
		return (-1);
	}
	phil->tab->locked_fork[phil->hold_r - 1] = 0;
	if (pthread_mutex_unlock(&phil->tab->forks[phil->hold_l - 1]) != 0)
	{
		phil->function_fail = 1;
		return (-1);
	}
	phil->tab->locked_fork[phil->hold_l - 1] = 0;
	return (0);
}

int	get_forks(t_philosopher *phil)
{
	if (pthread_mutex_lock(&phil->tab->forks[phil->hold_r - 1]) != 0)
	{
		phil->function_fail = 1;
		return (-1);
	}
	phil->tab->locked_fork[phil->hold_r - 1] = 1;
	// if (phil->nbr % 2 == 0)
	// 	pthread_mutex_lock(&phil->tab->forks[phil->hold_r - 1]);
	// else
	// 	pthread_mutex_lock(&phil->tab->forks[phil->hold_l - 1]);
	if (phil->dead_philosopher == 1)
		return (1);
	print_stuff(phil, "has taken a fork");
	if (pthread_mutex_lock(&phil->tab->forks[phil->hold_l - 1]) != 0)
	{
		phil->function_fail = 1;
		return (-1);
	}
	phil->tab->locked_fork[phil->hold_l - 1] = 1;
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
	t_philosopher	*phil;

	phil = (t_philosopher *)p;
	if (phil->nbr % 2 == 0)
		usleep(175);
	while (phil->dead_philosopher != 1 && !(phil->times_eaten
			== phil->times_to_eat && phil->arg_5 == 1))
	{
		if (get_forks(phil))
			break ;
		if (eat(phil) != 0)
			phil->function_fail = 1;
		if (phil->dead_philosopher == 1
			|| (phil->arg_5 == 1 && phil->times_eaten == phil->times_to_eat))
			break ;
		print_stuff(phil, "is sleeping");
		better_sleep(phil->time_sleep);
		if (phil->dead_philosopher == 1)
			break ;
		print_stuff(phil, "is thinking");
	}
	return (NULL);
}
