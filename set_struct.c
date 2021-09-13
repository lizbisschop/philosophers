#include "philo.h"

void    *set_struct(t_philos *philos, char **argv)
{
    philos->philo_dead = 0;
    philos->nb_philos = ft_atoi(argv[1]);
    return (0);
}