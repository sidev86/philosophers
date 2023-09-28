#include "philo.h"

long int get_current_time()
{
    struct timeval tv; 
    double time_in_ms;
    gettimeofday(&tv, NULL);
    time_in_ms = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000; 
    return (time_in_ms);
}

void start_threads(t_philo **philo, t_table **table)
{
    int i;
    
    i = 0;
    (*table)->start_time = get_current_time();
    //printf("start time %ld\n", table->start_time);
    while(i < (*table)->num_philos)
    {
        (*philo)[i].ph_thread = malloc(sizeof(pthread_t));
        pthread_create(&(*philo)[i].ph_thread, NULL, (void *)routine_thread, &(*philo)[i]);
        i++; 
    }
    (*table)->monitor_thread = malloc(sizeof(pthread_t));
    pthread_create(&(*table)->monitor_thread, NULL, (void *)monitor_thread, *philo);
}

void finish_threads(t_philo **philo, t_table **table)
{
    int i;
    
    i = 0;
    pthread_join((*table)->monitor_thread, NULL);
    while(i < (*table)->num_philos)
    {
        pthread_join((*philo)[i].ph_thread, NULL);
        i++; 
    }
}