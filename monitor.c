#include "philo.h"

void monitor_thread(void *ph)
{
    t_philo *philo = (t_philo*)ph;
    int i; 

    while (!philo->table->some_die)
    {
        i = 0; 
        while (i < philo->table->num_philos)
        {
            //printf("time to die = %d\n", philo->table->time_to_die);
            //printf("philo last meal = %ld\n", philo[i].last_meal);
        
            if (get_current_time() - philo[i].last_meal > philo->table->time_to_die && !philo[i].is_eating)
            {
                printf("meals eaten = %d\n", philo[i].meals_eaten);
                printf("is eating = %d\n", philo[i].is_eating);
                printf("time passed since last meal = %ld\n", get_current_time()- philo[i].last_meal);
                
                philo->table->some_die = 1; 
                break; 
            }
            i++; 
        }
        if (philo->table->some_die)
        {
            print_state(philo, "die");
            exit(1);
        }
    }
  
}