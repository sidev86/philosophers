#include "philo.h"


int main(int argc, char **argv)
{   
    t_table *table;
    t_philo *philo;

    table = 0; 
    philo = 0; 
    //1. check arguments validity
    if (check_args(argc, argv))
        return 1;
    //2. initialize data
    init_table(argc, argv, &table);
    init_philos(&philo, &table);
    if (init_mutexes(&table))
        return 1;
    //3. start threads
    start_threads(&philo, &table);
    //4. join threads
    finish_threads(&philo, &table);
    //5. free data
    return 0;
}