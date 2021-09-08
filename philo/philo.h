#ifndef philo_H
#define philo_H

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
	int	total_nbr;
	int nbr;
	int times_eaten;
	int dead_philosopher;
	int time_die;
	int time_eat;
	int	time_sleep;
	long long int last_time_eaten;
	int hold_r;
	int hold_l;
	int times_to_eat;
	int arg_5;
	int	dead;
	t_table *tab;
}				t_philosopher;

typedef struct	s_phil {
	int nb_philos;
	int philo_dead;
	pthread_t	dead_or_alive;
	t_philosopher	*p;
}				t_phil;


int				ft_atoi(const char *str);
int				ft_strncmp(char *str1, char *str2);
int				ft_strlen(const char *str);
int     	    threading(t_phil *phil, t_table *tab);
void    		*eat_sleep_think(void *p);
int				print_stuff(t_philosopher *phil, char *write);
void			*check_dead_or_alive(void *philosophers);
long long int	get_time(t_table *tab);

#endif
