#include "philo.h"

int all_meals_eaten(t_table *table, t_philo *philo)
{
    int i; 
    int philos_eat_all;

    i = 0;
    philos_eat_all = 0;  
    while (i < table->num_philos)
    {
        if (philo[i].meals_eaten == table->num_of_meals)
            philos_eat_all++;
        i++;
    }
    if (philos_eat_all == table->num_philos)
        return(1);
    else
        return(0);
}


void    *philo_monitor(void *ph)
{
    int i;
    t_philo *philo; 
    philo = (t_philo*)ph; 

    i = 0; 
    //printf("Time passed since last meal = %ld\n", get_current_time() - philo[i].last_meal);
    //printf("Someone died? %d\n", philo[i+1].table->someone_died);
    //printf("Philo Index = %d\n", philo[i+1].philo_index);
    //printf("time to die = %d\n", philo[i].table->time_to_die);
    
    while(!philo[i].table->someone_died)
    {
        if (all_meals_eaten(philo->table, philo) && philo->table->num_of_meals > 0)
        exit(1);
        while(i < philo[0].table->num_philos)
        {
            //printf("Time passed since last meal = %ld\n", get_current_time()- philo[i].last_meal);
            if (get_current_time() - philo[i].last_meal > philo[i].table->time_to_die && philo[i].last_meal > 0 && !philo[i].is_eating)
            {
                philo[i].table->someone_died = 1; 
                pthread_mutex_lock(&philo->table->print_out);
                printf("Time passed since last meal = %ld\n", get_current_time()- philo[i].last_meal);
                pthread_mutex_unlock(&philo->table->print_out);
                
                break; 
            }
            i++; 
        }
        if (philo[0].table->someone_died)
        {
            pthread_mutex_lock(&philo->table->print_out);
            printf("Philosopher %d died\n", philo[i].philo_index);
            pthread_mutex_unlock(&philo->table->print_out);
            exit(1);
        }
        i = 0; 
    }
   

    return (NULL); 
}