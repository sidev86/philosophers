#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>


typedef struct s_table
{
    int num_philos;
    int num_meals;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep; 
    int someone_died;
    int *forks;
    time_t start_time; 
    pthread_t *threads; 
    pthread_t monitor_thread; 
    pthread_mutex_t *forks_mutex; 
    pthread_mutex_t print_out;
}              t_table; 

typedef struct s_philo
{
    int philo_index; 
    int is_dead;
    int meals_eaten; 
    int eat_all_meals; 
    time_t last_meal;
    
    struct s_table *table;
}               t_philo;




void    *philo_routine(void *ph);
void    *philo_monitor(void *ph);
long    get_current_time();
