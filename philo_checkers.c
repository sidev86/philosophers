#include "philosopher.h"

int ft_isdigit(char *s)
{
    while(*s)
    {
        if (*s < '0' || *s > '9')
            return (0);
        s++;
    }
    return (1);
}
int ft_args_valid(int ac, char **av)
{
    int i; 

    i = 1; 
    if (ac < 5 || ac > 6)
    {
        print_error(ERR_NUM_ARGS);
        return(0);
    }
    else
    {
        while(i < ac)
        {
            if (!ft_isdigit(av[i]))
                print_error(ERR_ARG_NOT_VALID);
            i++;
        }
    }
    return (1);
}
