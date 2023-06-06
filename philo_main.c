#include "philosopher.h"

void print_error(char *str_err)
{
    printf("Error: %s\n", str_err);
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
    while(i < data->num_philos)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
    data->output_lock
}

int main(int argc, char **argv)
{
    t_data  data;
    if (!ft_args_valid(argc, argv))
        return(1);
    if (!ft_init_data(&data, argv, argc))
        return(1);
    ft_init_mutexes(&data, argv, argc);
}