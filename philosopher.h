#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

#define ERR_NUM_ARGS "Number of arguments not valid\n"
#define ERR_ARG_NOT_VALID "One or more arguments are not numbers\n"
#define ERR_NUM_PHILOS "Number of philosopher must be at least 1\n"
#define ERR_NUM_MEALS "Number of meals must be at least 1\n"

typedef struct s_philos
{
    int philo_id;
    int meals_took;
    int time_survive;
    int time_to_eat;
    int time_to_sleep;
    int stop;
    int num_philos;
    time_t initial_time;
    time_t last_meal_time;
    pthread_mutex_t *output_lock;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    struct s_data *data_table;
}               t_philos;

typedef struct s_data
{
    int num_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int some_dead;
    int num_meals;
    t_philos *all_philos;
    time_t initial_time;
    pthread_mutex_t *forks;
    pthread_mutex_t output_lock;
    pthread_t *threads;
    pthread_t philo_monitor;
}               t_data;


int ft_isdigit(char *s);
int ft_args_valid(int ac, char **av);
int ft_init_data(t_data *data, char **argv, int argc);
int ft_init_mutexes(t_data *data, char **argv, int argc);
int ft_init_threads(t_data *data, char **argv, int argc);
int ft_close_threads(t_data *data, char **argv, int argc);
int ft_init_philos_data(t_data *data, char **argv, int argc);
int ft_max_meals_eaten(t_philos *philo);
long int ft_get_time();


void    *philo_routine(void *ph);
void    *philo_monitor(void *ph);
void    take_forks(t_philos *philo);
void    eating_meal(t_philos *philo);
void    sleeping(t_philos *philo);
void    thinking(t_philos *philo);
void    print_error(char *str_err);


