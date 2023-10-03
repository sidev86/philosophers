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
        if (ft_atoi(argv[i]) < 1)
            return (1);
        i++;
    }
    return (0);
}

static int no_decimal_arg(int argc, char **argv)
{
    int i;
    int j; 

    i = 1;
    
    while (i < argc)
    {
        j = 0; 
        while(argv[i][j])
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
                return (1);
            j++;
        }
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
    if (no_positive_args(argc, argv) || no_decimal_arg(argc, argv))
    {
        print_error(ERR_INVALID_ARGS);
        return (1);
    }
    if (ft_atoi(argv[1]) > 250)
    {
        print_error(ERR_NUM_PHILOS_ARG);
        return (1);
    }  
    return (0);
}