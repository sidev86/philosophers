#include "philo.h"


void init_table(int argc, char **argv, t_table **table)
{
    *table = malloc(sizeof(t_table));
        
    (*table)->num_philos = atoi(argv[1]);
    (*table)->time_to_die = atoi(argv[2]);
    (*table)->time_to_eat = atoi(argv[3]);
    (*table)->time_to_sleep = atoi(argv[4]);
    (*table)->num_of_meals = -1;
    (*table)->some_die = 0;
    (*table)->eat_all = 0;
    if (argc == 6)
        (*table)->num_of_meals = atoi(argv[5]);
    (*table)->forks = malloc(sizeof(pthread_mutex_t) * (*table)->num_philos);
}

void init_philos(t_philo **philo, t_table **table)
{
    int i; 

    i = 0;
    *philo = malloc(sizeof(t_philo) * (*table)->num_philos);
    while (i < (*table)->num_philos)
    {
        (*philo)[i].philo_number = i + 1;
        (*philo)[i].meals_eaten = 0;
        (*philo)[i].eat_all_meals = 0;
        (*philo)[i].is_eating = 0; 
        (*philo)[i].table = (*table);  
        (*philo)[i].last_meal = get_current_time(); 
        i++; 
    }  
}

int init_mutexes(t_table **table)
{
    int i;

    i = 0;
    while (i < (*table)->num_philos)
    {
        if (pthread_mutex_init(&(*table)->forks[i], NULL) == 1)
            return(1);
        i++;
    }
    if (pthread_mutex_init(&(*table)->print_out, NULL) == 1)
        return(1);
    return (0);
}
