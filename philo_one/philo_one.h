#ifndef PHILO_ONE_H
#define PHILO_ONE_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct	s_table {
	pthread_mutex_t *forks;
	long long int	start_time;
	pthread_t 		*threads;
	pthread_mutex_t writing;

}				t_table;

typedef struct	s_philosopher {
	int nbr;
	int times_eaten;
	int time_die;
	int time_eat;
	int	time_sleep;
	int hold_r;
	int hold_l;
	int times_to_eat;
	int arg_5;
	int	dead;
	t_table *tab;
}				t_philosopher;

typedef struct	s_phil {
	int nb_philos;
	t_philosopher	*p;
}				t_phil;


int			ft_atoi(char *str);
int         threading(t_phil *phil, t_table *tab);
void    	*eat_sleep_think(void *p);
int			print_stuff(t_philosopher *phil, char *write);

#endif
