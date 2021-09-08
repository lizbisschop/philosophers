#include "philo.h"


//add pthread to the compile argument

int		print_return(const char *str)
{
	printf("%s", str);
	return (0);
}

void	info_philo(t_philosopher *phil, t_table *tab, char **argv, int nb, int argc)
{
	phil->nbr = nb;
	phil->total_nbr = ft_atoi(argv[1]);
	phil->time_die = ft_atoi(argv[2]);
	phil->time_eat = ft_atoi(argv[3]);
	phil->time_sleep = ft_atoi(argv[4]);
	phil->dead_philosopher = 0;
	phil->last_time_eaten = tab->start_time;
	// printf("what is in nbr = %d argv1 = %s\n", phil->nbr, argv[1]);
	if (argc == 6)
	{
		phil->times_to_eat = ft_atoi(argv[5]);
		phil->arg_5 = 1;
	}
	else phil->times_to_eat = 0;
	phil->times_eaten = 0;
	phil->hold_l = phil->nbr;
	phil->dead = 0;
	if (phil->nbr == 1)
		phil->hold_r = phil->nbr + 1;
	else
		phil->hold_r = phil->nbr - 1;
	// printf("hold_r = %d | hold_l = %d\n", phil->hold_r, phil->hold_l);
	phil->tab = tab;
}

int		set_philos(t_phil *phil, t_table *tab, char **argv, int argc)
{
	int i;

	i = 0;
	phil->p = (t_philosopher *)malloc(sizeof(t_philosopher)
		* phil->nb_philos + 1);
	if (!phil->p)
		return (-1);
	while (i < phil->nb_philos)
	{
		info_philo(&phil->p[i], tab, argv, i + 1, argc);
		i++;
	}
	return (0);
}

int		set_table(t_phil *phil, t_table *tab)
{
	int i;

	i = 0;
	tab->threads = (pthread_t *)malloc(sizeof(pthread_t) * phil->nb_philos);
	tab->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * phil->nb_philos);
	if (!tab->threads || !tab->forks)
		return (-1);
	while (i < phil->nb_philos)
	{
		pthread_mutex_init(&tab->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&tab->writing, NULL);
	return (0);
}

int     main(int argc, char **argv)
{
	t_phil phil;
	t_table tab;

	struct timeval time;
	gettimeofday(&time, NULL);
	tab.start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	if (argc <= 1 && argc <= 3)
		return (print_return("Not enough arguments\n"));
	if (ft_strncmp(argv[1], "1") && ft_strlen(argv[1]) == 1)
		return (print_return("Not enough philosophers\n"));
	phil.philo_dead = 0;
	phil.nb_philos = ft_atoi(argv[1]);
	if (set_table(&phil, &tab))
		return (print_return("Something wrong...\n"));
	set_philos(&phil, &tab, argv, argc);
	if (threading(&phil, &tab) == -1)
		return (-1);
	// (void)argc;
	return (0);
}