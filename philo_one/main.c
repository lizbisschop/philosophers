#include "philo_one.h"


//add pthread to the compile argument

int		set_philos(t_phil *phil, char **argv)
{
	int i;

	i = 0;
	phil->nb_philos = ft_atoi(argv[1]);
	phil->p = (t_philosopher *)malloc(sizeof(t_philosopher)
		* phil->nb_philos + 1);
	if (!phil->p)
		return (-1);
	while (i < phil->nb_philos)
	{
		phil->p[i].nbr = i + 1;
		phil->p[i].time_die = ft_atoi(argv[2]);
		phil->p[i].time_eat = ft_atoi(argv[3]);
		phil->p[i].time_sleep = ft_atoi(argv[4]);
		i++;
	}
	return (0);
}

int     main(int argc, char **argv)
{
	t_phil phil;
	t_table tab;

	if (argc == 1)
		return (0);
	set_philos(&phil, argv);
	if (threading(&phil, &tab) == -1)
		return (-1);
	
	(void)argc;
}