#ifndef PHILO_H
# define PHILO_H

# define ERR_NUM_ARGS "Number of arguments invalid. Must be between 5 and 6."
# define ERR_INVALID_ARGS "One or more arguments are not valid."
# define ERR_NUM_PHILOS_ARG "Number of philosophers cannot be more than 250"

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

typedef struct s_table
{
	int				num_philos;
	int				num_of_meals;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				some_die;
	int				all_philos_eat;
	long			start_time;
	pthread_t		monitor_thread;
	pthread_mutex_t last_meal_lock; 
	pthread_mutex_t	print_out;
	pthread_mutex_t	*forks;
}		t_table;

typedef struct s_philo
{
	int				philo_number;
	int				meals_eaten;
	int				eat_all_meals;
	int				is_eating;
	long			last_meal;
	pthread_t		ph_thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_table			*table;
}		t_philo;

int			check_args(int argc, char **argv);
int			init_mutexes(t_table **table);
int			ft_atoi(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		print_error(char *msg);
void		start_threads(t_philo **philo, t_table **table);
void		finish_threads(t_philo **philo, t_table **table);
void		init_table(int argc, char **argv, t_table **table);
void		init_philos(t_philo **philo, t_table **table);
void		routine_thread(void *ph);
void		monitor_thread(void *ph);
void		print_state(t_philo *philo, char *state);
void		free_data(t_table *table, t_philo *philo);
long		get_current_time(void);
#endif
