#include "philosopher.h"

void    one_philo_fork(t_philos *philo)
{
     time_t actual_time;

     actual_time = ft_get_time();
     pthread_mutex_lock(philo->left_fork);
     pthread_mutex_lock(philo->output_lock);
     printf("%ld %d has taken a fork\n",(actual_time - philo->initial_time),  philo->philo_id);
     pthread_mutex_unlock(philo->output_lock);
}


void    *philo_routine(void *ph)
{
    t_philos *philo; 

    philo = (t_philos*)ph;
    philo->initial_time = ft_get_time();
    philo->last_meal_time = ft_get_time();
  
    while (1)
    {
        if (philo->data_table->some_dead || ft_max_meals_eaten(philo) || philo->stop)
            return(NULL);
        take_forks(philo);
        if (philo->data_table->some_dead || ft_max_meals_eaten(philo) || philo->stop)
            return(NULL);
        eating_meal(philo);
        if (philo->data_table->some_dead || ft_max_meals_eaten(philo) || philo->stop)
            return(NULL);
        sleeping(philo);
         if (philo->data_table->some_dead || ft_max_meals_eaten(philo) || philo->stop)
            return(NULL);
        thinking(philo); 
    }
    return (NULL);
}

void    stop_all_philos(t_philos *philos)
{
    int i; 

    i = -1; 

    while (++i < philos[0].num_philos)
        philos[i].stop = 1; 
}

void    *philo_monitor(void *ph)
{
    t_philos *philo;
    time_t actual_time;
    int i;

    i = 0;
    philo = (t_philos*)ph;
    while(!philo[i].stop)
    {
        i = 0; 
        while (i < philo->num_philos)
        {
            //printf("olalaaaa\n");
            actual_time = ft_get_time();
            if(actual_time - philo[i].last_meal_time > philo[i].time_survive)
            {
                philo[i].data_table->some_dead = 1;
                pthread_mutex_lock(philo[i].output_lock); 
                //printf("some deady = %d\n", philo[i].data_table->some_dead);
                printf("%ld %d died\n",(actual_time - philo[i].initial_time),  philo[i].philo_id);
                pthread_mutex_unlock(philo[i].output_lock); 
                stop_all_philos(philo->data_table->all_philos);
                return(NULL);
            }
            i++;
        }
    }
  
    return (NULL);

}