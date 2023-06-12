#include "philosopher.h"

int    ft_init_data(t_data *data, char **argv, int argc)
{
    data->some_dead = 0; 
    data->num_philos = (atoi(argv[1]));
    data->time_to_die = (atoi(argv[2]));
    data->time_to_eat = (atoi(argv[3]));
    data->time_to_sleep = (atoi(argv[4]));
    if (argc == 5)
        data->num_meals = -1;
    else 
        data->num_meals = (atoi(argv[5]));
    if (data->num_philos < 1)
    {
        print_error(ERR_NUM_PHILOS);
        return (0);
    }   
    if (argc == 6)
    {
        data->num_meals = (atoi(argv[5]));
        if (data->num_meals < 1)
        {
            print_error(ERR_NUM_MEALS);
            return (0);
        }      
    }
    return (1);
}

int ft_init_mutexes(t_data *data, char **argv, int argc)
{
    int i;

    i = 0;

    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    if (!data->forks)
        return (0);
    while(i < data->num_philos)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&data->output_lock, NULL);
    return (1);
}


int ft_init_threads(t_data *data, char **argv, int argc)
{
    int i; 
    int j; 
    pthread_t *thread; 
    pthread_t monitor_th;

    i = 0; 
    j = 0; 
    thread = malloc(sizeof(pthread_t) * data->num_philos);
    while (i < data->num_philos)
    {
        //printf("creo thread\n");
        pthread_create(&thread[i], NULL, &philo_routine, (void*)&data->all_philos[i]);
        i++;
    }
    pthread_create(&monitor_th, NULL, &philo_monitor, (void*)data->all_philos);
    //pthread_join(monitor_th, NULL);
    data->threads = thread; 
    return (1);
}

int ft_init_philos_data(t_data *data, char **argv, int argc)
{
    t_philos *philos;
    int i;

    i = 0;
    philos = malloc(sizeof(t_philos) * data->num_philos);
    if (!philos)
        return (0);
    while(i < data->num_philos)
    {
        philos[i].philo_id = i + 1;
        //printf("Philosopher id = %d\n", philos[i].philo_id);
        philos[i].meals_took = 0; 
        philos[i].time_survive = data->time_to_die;
        philos[i].time_to_eat = data->time_to_eat;
        philos[i].time_to_sleep = data->time_to_sleep;
        //printf("Last meal time filosofo %d = %ld\n", philos[i].philo_id, philos[i].last_meal_time);
        philos[i].stop = 0; 
        philos[i].left_fork = &(data->forks[i]);
        philos[i].right_fork = &(data->forks[(i + 1) % (data->num_philos)]);
        philos[i].output_lock = &(data->output_lock);
        philos[i].num_philos = (data->num_philos);
        philos[i].data_table = data; 
        //printf("Indice forchetta sinistra filosofo %d = %d\n", philos[i].philo_id, i);
        //printf("Indice forchetta destra filosofo %d = %d\n", philos[i].philo_id, (i + 1) % (data->num_philos));
        i++;
    }
    data->all_philos = philos;
    return (1);
}

int ft_close_threads(t_data *data, char **argv, int argc)
{
    int i; 

    i = 0; 

    if(data->num_philos == 1)
        pthread_mutex_unlock(data->all_philos[0].left_fork);
    while (i < data->num_philos)
    {
        pthread_join(data->threads[i], NULL);
        i++;
    }
    return (1);
}