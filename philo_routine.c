#include "philosopher.h"

void    *philo_routine(void *ph)
{
    t_philos *philo; 

    philo = (t_philos*)ph;
    
    printf("Philo %d routine\n", philo->philo_id);
    while (1)
    {
        //taking forks
        take_forks(philo);
        //eat (if has got forks)
        //eating_meal(philo);
        //sleep (when he finishes eat)
        //sleeping(philo);
        //think (when he finishes sleep)
        //thinking(philo); 
    }
    return (NULL);
}

void    *philo_monitor(void *ph)
{
    t_philos *philo;
    int i;

    i = 0;
    philo = (t_philos*)ph;
    printf("Philo monitor\n");

    //in questo thread devo controllare se tutti i filosofi hanno raggiunto il numero di pasti totale
    //(nel caso in cui aggiungo il parametro opzionale num di pasti max)
    //oppure se uno dei filosofi e' morto
  

}