#include "philo.h"

void	ft_usleep(unsigned int n)
{
	long	start;
	long	step;

	start = get_current_time();
	while (1)
	{
		step = get_current_time();
		if ((step - start) * 1000 >= n)
			break ;
		usleep(500);
	}
}


void    *one_philo_routine(void *ph)
{
    t_philo *philo; 
    time_t current_time; 
    
    philo = (t_philo*)ph; 
    philo->last_meal = get_current_time();
    current_time = get_current_time() - philo->table->start_time; 
        pthread_mutex_lock(&philo->table->print_out);
    printf("%ld ms %d is thinking\n", current_time, philo->philo_index); 
    pthread_mutex_unlock(&philo->table->print_out);
    return (NULL);
}


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
    
    while(!philo->table->someone_died)
    {
        //pthread_mutex_lock(&philo->table->print_out);
        //printf("Indici forchette %d: %d %d \n",philo->philo_index, philo->table->forks[rf_index],!philo->table->forks[lf_index]);
        //pthread_mutex_unlock(&philo->table->print_out);
            //printf("thread routine\n");
            
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
            pthread_mutex_lock(&philo->table->print_out);
            current_time = get_current_time() - philo->table->start_time; 
            //printf("Indice forchetta destra = %d\n", rf_index); 
            //printf("Indice forchetta sinistra = %d\n", lf_index); 
            if (philo->table->someone_died) return (NULL); 
            
            printf("%ldms %d has taken a fork\n", current_time, philo->philo_index); 
            printf("%ldms %d has taken a fork\n", current_time, philo->philo_index); 
            pthread_mutex_unlock(&philo->table->print_out);
          
    
            //PHILO IS EATING
            //printf("filosofo %d mangiare\n", philo->philo_index); 
            pthread_mutex_lock(&philo->table->print_out);
            current_time = get_current_time() - philo->table->start_time;
            philo->last_meal = get_current_time();
            
            if (philo->table->someone_died) return (NULL); 
           
            philo->is_eating = 1; 
           
            printf("%ldms %d is eating.\n", current_time, philo->philo_index);
            if (philo->table->num_of_meals >= 0)
            {
                philo->meals_eaten++; 
                printf("Meals eaten = %d\n", philo->meals_eaten); 
            }
                
            
            pthread_mutex_unlock(&philo->table->print_out);
            ft_usleep(philo->table->time_to_eat * 1000);
            
            philo->is_eating = 0; 
            pthread_mutex_unlock(&philo->table->forks_mutex[rf_index]);
            pthread_mutex_unlock(&philo->table->forks_mutex[lf_index]);

            //philo->table->forks[rf_index] = 0; 
            //philo->table->forks[lf_index] = 0; 
            
            //printf("philo last meal after eats : %ld\n", philo->last_meal);
            pthread_mutex_lock(&philo->table->print_out);
            //PHILO IS SLEEPING
            if (philo->table->someone_died) return (NULL); 
            current_time = get_current_time() - philo->table->start_time; 
            
            printf("%ldms %d is sleeping\n", current_time, philo->philo_index); 
            pthread_mutex_unlock(&philo->table->print_out);
            ft_usleep(philo->table->time_to_sleep * 1000);

            //PHILO IS THINKING
            if (philo->table->someone_died) return (NULL); 
            current_time = get_current_time() - philo->table->start_time; 
             pthread_mutex_lock(&philo->table->print_out);
            printf("%ldms %d is thinking\n", current_time, philo->philo_index); 
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