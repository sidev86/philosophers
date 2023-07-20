#include "philo.h"

void    *philo_routine(void *ph)
{
    t_philo *philo; 
    time_t current_time; 
    int rf_index;
    int lf_index; 
    

    philo = (t_philo*)ph; 
    rf_index = philo->philo_index - 1;
    lf_index = philo->philo_index % philo->table->num_philos;
    philo->table->forks[rf_index] = 0; 
    philo->table->forks[lf_index] = 0; 
    
    while(!philo->is_dead)
    {
        //pthread_mutex_lock(&philo->table->print_out);
        //printf("Indici forchette %d: %d %d \n",philo->philo_index, philo->table->forks[rf_index],!philo->table->forks[lf_index]);
        //pthread_mutex_unlock(&philo->table->print_out);
        
            
            //PHILO TAKING FORKS
            /*pthread_mutex_lock(&philo->table->print_out);
            printf("filosofo %d prende forchets\n", philo->philo_index); 
            printf("Indici forchette filosofo %d : %d %d \n",philo->philo_index,philo->table->forks[rf_index],philo->table->forks[lf_index]);
            pthread_mutex_unlock(&philo->table->print_out);*/
            pthread_mutex_lock(&philo->table->forks_mutex[rf_index]);
            pthread_mutex_lock(&philo->table->forks_mutex[lf_index]);
            //philo->table->forks[rf_index] = 1; 
            //philo->table->forks[lf_index] = 1; 
            //philo->has_forks = 1; 
            current_time = get_current_time() - philo->table->start_time; 
            //printf("Indice forchetta destra = %d\n", rf_index); 
            //printf("Indice forchetta sinistra = %d\n", lf_index); 
            pthread_mutex_lock(&philo->table->print_out);
            printf("%ld ms %d has taken a fork\n", current_time, philo->philo_index); 
            printf("%ld ms %d has taken a fork\n", current_time, philo->philo_index); 
            pthread_mutex_unlock(&philo->table->print_out);
          
    
            //PHILO IS EATING
            //printf("filosofo %d mangiare\n", philo->philo_index); 
            philo->last_meal = get_current_time();
            current_time = get_current_time() - philo->table->start_time; 
            pthread_mutex_lock(&philo->table->print_out);
            printf("%ld ms %d is eating\n", current_time, philo->philo_index);
            pthread_mutex_unlock(&philo->table->print_out);
            
            usleep(philo->table->time_to_eat * 1000);
            philo->last_meal = get_current_time();
            pthread_mutex_unlock(&philo->table->forks_mutex[rf_index]);
            pthread_mutex_unlock(&philo->table->forks_mutex[lf_index]);

            //philo->table->forks[rf_index] = 0; 
            //philo->table->forks[lf_index] = 0; 
            
            //printf("philo last meal after eats : %ld\n", philo->last_meal);
             
            //PHILO IS SLEEPING
           
            current_time = get_current_time() - philo->table->start_time; 
            pthread_mutex_lock(&philo->table->print_out);
            printf("%ld ms %d is sleeping\n", current_time, philo->philo_index); 
            pthread_mutex_unlock(&philo->table->print_out);
            usleep(philo->table->time_to_sleep * 1000);

            //PHILO IS THINKING
            current_time = get_current_time() - philo->table->start_time; 
             pthread_mutex_lock(&philo->table->print_out);
            printf("%ld ms %d is thinking\n", current_time, philo->philo_index); 
            pthread_mutex_unlock(&philo->table->print_out);
    }
  
    
     //pthread_mutex_lock(&philo->tables->taking_forks);
    /*if (philo->tables->forks[0] == 0)
    {
        printf("entro if\n");
       
        //philo->forks[rf_index] = 1; 
        //philo->forks[lf_index] = 1; 
        //printf("Philosopher %d taking forks\n", philo->philo_index);
        usleep(1000 * 1000);
    }*/
     //pthread_mutex_unlock(&philo->tables->taking_forks);


    return (NULL);
}