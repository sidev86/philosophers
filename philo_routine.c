#include "philosopher.h"

void    *philo_routine(void *ph)
{
    t_philos *philo; 

    philo = (t_philos*)ph;

    while (1)
    {
        //taking forks
        take_forks(philo);
        //eat (if has got forks)
        eating_meal(philo);
        //sleep (when he finishes eat)
        sleeping(philo);
        //think (when he finishes sleep)
        thinking(philo); 
    }
    return (NULL);
}