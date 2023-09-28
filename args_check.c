#include "philo.h"


static int invalid_args_num(int argc)
{
    return (argc < 5 || argc > 6);
}

static int no_positive_args(int argc, char **argv)
{
    int i;

    i = 1; 
    while (i < argc)
    {
        if (atoi(argv[i]) < 1)
            return (1);
        i++;
    }
    return (0);
}

int check_args(int argc, char **argv)
{

    if (invalid_args_num(argc))
    {
        print_error(ERR_NUM_ARGS);
        return (1);
    }
    if (no_positive_args(argc, argv))
    {
        print_error(ERR_INVALID_ARGS);
        return (1);
    }
    if (atoi(argv[1]) > 250)
    {
        print_error(ERR_NUM_PHILOS_ARG);
        return (1);
    }  
    return (0);
}