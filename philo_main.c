#include "philosopher.h"

void print_error(char *str_err)
{
    printf("Error: %s\n", str_err);
}

long int ft_get_time()
{
    struct timeval tv;
    long int    time;

    gettimeofday(&tv, NULL);
    time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (time);  
}

int    ft_init_data(t_data *data, char **argv, int argc)
{
    data->some_dead = 0; 
    data->num_philos = (atoi(argv[1]));
    data->time_to_die = (atoi(argv[2]));
    data->time_to_eat = (atoi(argv[3]));
    data->time_to_sleep = (atoi(argv[4]));
    data->num_meals = -1;
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
        philos[i].meals_took = 0; 
        philos[i].time_to_die = data->time_to_die;
        philos[i].time_to_eat = data->time_to_eat;
        philos[i].time_to_sleep = data->time_to_sleep;
        philos[i].last_meal_time = ft_get_time();
        philos[i].all_meals_eaten = 0; 
        philos[i].left_fork = &(data->forks[philos[i].philo_id]);
        philos[i].right_fork = &(data->forks[philos[i].philo_id + 1]);
        i++;
    }
    return (1);
}

int main(int argc, char **argv)
{
    t_data  data;
    if (!ft_args_valid(argc, argv))
        return (1);
    if (!ft_init_data(&data, argv, argc))
        return (1);
    if (!ft_init_mutexes(&data, argv, argc))
        return (1);
    ft_init_data_philos(&data, argv, argc);
}