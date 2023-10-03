#include "philo.h"

void free_data(t_table *table, t_philo *philo)
{
    int i; 

    i = 0; 
    free(table->monitor_thread);
    while (i < philo->table->num_philos)
    {
        free(philo[i].ph_thread);
    }
    exit(1); 
}