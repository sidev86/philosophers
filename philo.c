#include "philo.h"


int args_num_valid(int argc)
{
    if (argc < 5 || argc > 6)
    {
        printf("Error! Number of arguments invalid\n");
        return(0);
    }
    return(1);  
}

int args_values_ok(int argc, char **argv)
{
    int i;

    i = 0; 
    //controllo validità primo argomento
    if (atoi(argv[1]) < 1)
    {
        printf("Error! The first argument (Number of Philosopher) must be a number between 1 and 250\n");
        return (0);
    }
    if (argc == 6)
    {
        if(atoi(argv[5]) < 1)
        {
            printf("Error! The optional argument (Number of meals) must be at least 1\n");
            return (0);
        }
    }
    return (1);  
}

long get_current_time()
{
    struct timeval tv; 
    double time_in_ms;
    gettimeofday(&tv, NULL);
    time_in_ms = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000; 
    return (time_in_ms);
}

void    init_data(t_philo **philo, t_table **table, char **argv, int argc)
{
    int i;

    i = 0; 
    *table = malloc(sizeof(t_table));

    (*table)->num_philos = atoi(argv[1]);
    (*table)->time_to_die = atoi(argv[2]);
    (*table)->time_to_eat = atoi(argv[3]);
    (*table)->time_to_sleep = atoi(argv[4]);
    
    if (argc == 6)
        (*table)->num_of_meals = atoi(argv[5]);
    else 
        (*table)->num_of_meals = -1; 
    
    (*table)->start_time = get_current_time();
    printf("Actual time in ms : %ld\n", (*table)->start_time);
    
    printf("Time elapsed : %ld ms\n", get_current_time() - (*table)->start_time);
    printf("Number of philosophers = %d\n", (*table)->num_philos);
    printf("Time to die = %d\n", (*table)->time_to_die);
    printf("Time to eat = %d\n", (*table)->time_to_eat);
    printf("Time to sleep = %d\n", (*table)->time_to_sleep);
    printf("Number of meals = %d\n", (*table)->num_of_meals);

    *philo = malloc(sizeof(t_philo) * (*table)->num_philos);
    if (*philo == NULL) 
        printf("errore di allocazione\n");

    
    while (i < (*table)->num_philos) 
    {
        (*philo)[i].philo_index = i + 1;
        (*philo)[i].eat_all_meals = 0;
        (*philo)[i].is_dead = 0;
        (*philo)[i].meals_eaten = 0;
        (*philo)[i].table = (*table);
        (*philo)[i].table->someone_died = 0; 
        (*philo)[i].last_meal = 0; 
        (*philo)[i].is_eating = 0; 
        //printf("Someone died:::%d\n\n", (*philo)[i].table->someone_died);
        i++;
    }
    (*philo)->table->forks = malloc(sizeof(int) * (*table)->num_philos);
    (*table)->forks_mutex = malloc(sizeof(pthread_mutex_t) * (*table)->num_philos);
    //inizializzo tutte le forchette a 0 (forchette sul tavolo)
    i = 0; 
    while (i < (*table)->num_philos) 
    {
        (*table)->forks[i] = 0;
        pthread_mutex_init(&(*table)->forks_mutex[i], NULL);
        i++;
    }
 
}

void    init_mutex(t_philo **philo, t_table **table)
{
    printf("Inizializzo mutex\n");
    pthread_mutex_init(&(*table)->print_out, NULL); 
}
void start_threads(t_philo **philo, t_table **table)
{
    int i;
    pthread_t *thread;

    i = 0; 
    thread = malloc(sizeof(pthread_t) * (*table)->num_philos);
    //(*table)->monitor_thread = malloc(sizeof(pthread_t)); 
    if ((*table)->num_philos == 1)
        pthread_create(&thread[i], NULL, &one_philo_routine, &(*philo)[i]);

    else
    {
        while (i < (*table)->num_philos)
        {
            //printf("Creo Threadd\n");
            pthread_create(&thread[i], NULL, &philo_routine, &(*philo)[i]);
            i++;
        }
    }
   
    i = 0;
    //usleep(10 * 1000);
    //printf("Creo Monitor Thread\n");
    pthread_create(&(*table)->monitor_thread, NULL, &philo_monitor, *philo); 
    (*table)->threads = thread; 
}

void finish_threads(t_philo **philo, t_table **table)
{
    int i; 

    i = 0; 
    pthread_join((*table)->monitor_thread, NULL); 
    while (i < (*table)->num_philos)
    {
        pthread_join((*table)->threads[i], NULL);
        i++; 
    }
}

int main(int argc, char **argv)
{
    t_philo *philo; 
    t_table *table; 
    
    table = malloc(sizeof(t_table));
    
    //controllo numero di argomenti
    if (!args_num_valid(argc))
        return(1);
    //se numero di argomenti è corretto controllo validità argomenti
    if (!args_values_ok(argc, argv))
        return(1);
    //inizializzo strutture dati
    init_data(&philo, &table, argv, argc);
    //inizializzo mutex
    init_mutex(&philo, &table);
    //creo i thread
    start_threads(&philo, &table);
    //resto in attesa della terminazione di tutti i thread
    finish_threads(&philo, &table);
}