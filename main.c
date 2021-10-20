#include "philo.h"

int	print_return(const char *str)
{
	printf("%s", str);
	return (0);
}

int	init_philo(t_philosopher *p, t_table *tab, int nb, char **argv, int argc)
{
	p->nbr = nb;
	p->total_nbr = ft_atoi(argv[1]);
	p->time_die = ft_atoi(argv[2]);
	p->time_eat = ft_atoi(argv[3]);
	p->time_sleep = ft_atoi(argv[4]);
	p->dead_philosopher = 0;
	p->is_eating = 0;
	p->last_time_eaten = tab->start_time;
	if (argc == 6)
	{
		p->times_to_eat = ft_atoi(argv[5]);
		p->arg_5 = 1;
	}
	else
		p->times_to_eat = 0;
	p->times_eaten = 0;
	p->hold_r = p->nbr;
	p->dead = 0;
	if (p->nbr == 1)
		p->hold_l = p->total_nbr;
	else
		p->hold_l = p->nbr - 1;
	p->tab = tab;
	return (0);
}

int	set_philos(t_philos *philos, t_table *tab, char **argv, int argc)
{
	int	i;

	i = 1;
	philos->p = (t_philosopher *)malloc(sizeof(t_philosopher)
			* philos->nb_philos + 1);
	if (!philos->p)
		return (-1);
	while (i < argc)
	{
		if (!is_number(argv[i]))
			return (-1);
		i++;
	}
	i = 0;
	while (i < philos->nb_philos)
	{
		init_philo(&philos->p[i], tab, i + 1, argv, argc);
		i++;
	}
	return (0);
}

int	set_table(t_philos *philos, t_table *tab)
{
	int	i;

	i = 0;
	tab->threads = (pthread_t *)malloc(sizeof(pthread_t) * philos->nb_philos);
	tab->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* philos->nb_philos);
	if (!tab->threads || !tab->forks)
		return (-1);
	tab->locked_fork = (int *)malloc(sizeof(int) * philos->nb_philos + 1);
	while (i < philos->nb_philos)
	{
		tab->locked_fork[i] = 0;
		i++;
	}
	i = 0;
	while (i < philos->nb_philos)
	{
		if (pthread_mutex_init(&tab->forks[i], NULL) != 0)
		{
			philos->function_fail = 1;
			return (-1);
		}
		i++;
	}
	if (pthread_mutex_init(&tab->writing, NULL) != 0)
	{
		philos->function_fail = 1;
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philos		philos;
	t_table			tab;
	struct timeval	time;

	gettimeofday(&time, NULL);
	tab.start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	if (argc <= 4 || argc > 6)
		return (print_return("Not the right amount of arguments\n"));
	if (ft_strncmp(argv[1], "1") && ft_strlen(argv[1]) == 1)
	{
		return (printf("%lli 1 Died\n", tab.start_time - get_time(&tab)));
	}
	set_struct(&philos, argv);
	if (set_table(&philos, &tab) || philos.nb_philos == 0)
	{
		if (philos.function_fail == 1)
			return (print_return("function failed\n"));
		return (print_return("Someting wrong...\n"));
	}
	if (set_philos(&philos, &tab, argv, argc) || philos.p->time_die == 0
		|| philos.p->time_eat == 0 || philos.p->time_sleep == 0
		|| philos.p->time_sleep == 0)
		return (print_return("Something went wrong...\n"));
	if (threading(&philos, &tab) == -1)
	{
		if (philos.function_fail == 1)
			return (print_return("function failed\n"));
		if (philos.philo_dead == 1)
			return (print_return("Philosopher died\n"));
		return (print_return("Something went wrong...\n"));
	}
	return (0);
}
