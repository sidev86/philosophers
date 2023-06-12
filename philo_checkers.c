#include "philosopher.h"

int ft_isdigit(char *s)
{
    while(*s)
    {
        if (*s < '0' || *s > '9')
            return (0);
        s++;
    }
    return (1);
}
int ft_args_valid(int ac, char **av)
{
    int i; 

    i = 1; 
    if (ac < 5 || ac > 6)
    {
        print_error(ERR_NUM_ARGS);
        return(0);
    }
    else
    {
        while(i < ac)
        {
            if (!ft_isdigit(av[i]))
            {
                print_error(ERR_ARG_NOT_VALID);
                return(0);
            }
                
            i++;
        }
    }
    return (1);
}

int ft_max_meals_eaten(t_philos *philo)
{
    
    int i = 0; 

    while (i < philo->num_philos)
    {
        pthread_mutex_lock(philo->output_lock);
        //printf("Meals of philosopher %d tookeeee = %d\n", philo->data_table->all_philos[i].philo_id, philo->meals_took);
        pthread_mutex_unlock(philo->output_lock);
        i++;
    }
   
    if (philo->meals_took > 0 && philo->data_table->num_meals != -1)
    {
        if(philo->meals_took > philo->data_table->num_meals)
            philo->stop = 1; 
    }
    return (0);
}
