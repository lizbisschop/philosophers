#include "philo.h"

long long int	get_time(t_table *tab)
{
	struct timeval	time;
	int				ret;

	ret = gettimeofday(&time, NULL);
	if (ret == -1)
	{
		printf("gettimeday() failed\n");
		return (-1);
	}
	return ((time.tv_sec * 1000) + time.tv_usec / 1000);
}

void	print_stuff(t_philosopher *phil, char *write)
{
	long long int	ret_time;

	ret_time = get_time(phil->tab);
	if (ret_time == -1)
	{
		phil->function_fail = 1;
		return ;
	}
	if (pthread_mutex_lock(&phil->tab->writing) != 0)
	{
		phil->function_fail = 1;
		return ;
	}
	printf("%lli %i %s", ret_time - phil->tab->start_time, phil->nbr, write);
	if (ft_strncmp(write, "is eating") && ft_strlen(write) == 9)
		printf(" [%d]", phil->times_eaten);
	printf("\n");
	if (pthread_mutex_unlock(&phil->tab->writing) != 0)
	{
		phil->function_fail = 1;
		return ;
	}
}
