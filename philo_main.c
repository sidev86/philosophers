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


int main(int argc, char **argv)
{
    t_data  data;
    if (!ft_args_valid(argc, argv))
        return (1);
    if (!ft_init_data(&data, argv, argc))
        return (1);
    if (!ft_init_mutexes(&data, argv, argc))
        return (1);
    if (!ft_init_philos_data(&data, argv, argc))
        return (1);
    if (!ft_init_threads(&data, argv, argc))
        return (1);
    ft_end_threads(&data, argv, argc);
}