#include "philo.h"
void    *philo_monitor(void *ph)
{
    int i;
    t_philo *philo; 
    philo = (t_philo*)ph; 

    i = 0; 
    //printf("Time passed since last meal = %ld\n", get_current_time() - philo[i].last_meal);
    //printf("Someone died? %d\n", philo[i+1].table->someone_died);
    //printf("Philo Index = %d\n", philo[i+1].philo_index);
    printf("time to die = %d\n", philo[i].table->time_to_die);
    while(!philo[i].table->someone_died)
    {

        while(philo[i].philo_index < philo[i].table->num_philos)
        {
            //printf("Time passed since last meal = %ld\n", get_current_time()- philo[i].last_meal);
            if (get_current_time() - philo[i].last_meal > philo[i].table->time_to_die && philo[i].last_meal > 0)
            {
                printf("Time passed since last meal = %ld\n", get_current_time()- philo[i].last_meal);
                philo[i].table->someone_died = 1; 
                break; 
            }
            i++; 
        }
        if (philo[i].table->someone_died)
        {
            printf("Philosopher %d died!\n", philo[i].philo_index);
            exit(1);
        }
        i = 0; 
    }
   

    return (NULL); 
}