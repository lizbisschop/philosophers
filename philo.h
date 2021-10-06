#ifndef philo_H
#define philo_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

//REMOVE!!!!!!!!!!!!!!!!
#include <errno.h>
#include <string.h>

#define MAX_INT = 2147483647;
#define MIN_INT = -2147483648;

typedef struct	s_table {
	pthread_mutex_t *forks;
	int		*locked_fork;
	long long int	start_time;
	pthread_t 		*threads;
	pthread_mutex_t writing;

}				t_table;

typedef struct	s_philosopher {
	int	function_fail;
	int	total_nbr;
	int nbr;
	int is_eating;
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

typedef struct	s_philos {
	int nb_philos;
	int philo_dead;
	pthread_t	dead_or_alive;
	long long int start_time;
	t_philosopher	*p;
	int	function_fail;
}				t_philos;


int				ft_atoi(const char *str);
int				is_number(char *str);
void			*set_struct(t_philos *philos, char **argv);
int				ft_strncmp(char *str1, char *str2);
int				ft_strlen(const char *str);
int     	    threading(t_philos *phil, t_table *tab);
void    		*eat_sleep_think(void *p);
void			print_stuff(t_philosopher *phil, char *write);
void			*check_dead_or_alive(void *philosophers);
long long int	get_time(t_table *tab);
void    	better_sleep(int ms);

#endif
