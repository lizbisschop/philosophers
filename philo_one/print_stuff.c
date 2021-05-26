#include "philo_one.h"

long long int	get_time(t_table *tab)
{
	struct	timeval time;
	int		ret;

	ret = gettimeofday(&time, NULL);
	if (ret  == -1)
	{
		pthread_mutex_lock(&tab->writing);
		printf("gettimeday() failed\n");
		pthread_mutex_unlock(&tab->writing);
		return (0);
	}
	return ((time.tv_sec * 1000) + time.tv_usec / 1000);
	(void)tab;
}

int        		print_stuff(t_philosopher *phil, char *write)
{
	long long int ret_time;

	ret_time = get_time(phil->tab);
	if (ret_time == -1)
		return (-1);
	pthread_mutex_lock(&phil->tab->writing);
	// printf("waiting or nott??\n");
	printf("%lli %i %s\n", ret_time - phil->tab->start_time, phil->nbr, write);
	pthread_mutex_unlock(&phil->tab->writing);
	return (0);
}