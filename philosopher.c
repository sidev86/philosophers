#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define TABLE 1;
#define IN_HAND 0;

enum ph_state
{
    eating,
    sleeping,
    thinking
};


typedef struct s_philos
{
    pthread_t philo_thread;
    int seat; 
    int left_fork;
    int right_fork; 
    enum ph_state state;
}               t_philos; 

typedef struct s_data
{
    int num_philos;
    int time_to_die; 
    int time_to_eat;
    int time_to_sleep;
    int *forks; 
    t_philos *philo;
}               t_data; 

void    *philo_routine(void *arg)
{
    t_philos *ph = (t_philos*)arg;
    int ind = ph->seat;
    //printf("philo state in routine = %d\n", ph->state);
    printf("Philosopher %d thread created\n", ph->seat);
    if (ph->state == thinking && ph->left_fork == 1 && ph->right_fork == 1)
        printf("Philosopher %d has forks\n", ph->seat);


    /*else if (ph->state == eating)
        printf("Philosopher %d is eating\n", ph->seat);
    else if (ph->state == sleeping)
        printf("Philosopher %d is sleeping\n", ph->seat);*/
    
    return (0);
}

int main(int argc, char **argv)
{
    t_data *data; 
    t_philos *philo;
    int i = 0;
    if (argc == 5)
    {
        data = malloc(sizeof(t_data));
    
        data->num_philos = atoi(argv[1]);
        data->time_to_die = atoi(argv[2]);
        data->time_to_eat = atoi(argv[3]);
        data->time_to_sleep = atoi(argv[4]);
        
        data->philo = malloc(sizeof(t_philos) * data->num_philos);
        data->forks = malloc(sizeof(int) * data->num_philos);
     
        printf("Number of philosophers = %d\n", data->num_philos);
        printf("Time to die = %d\n", data->time_to_die);
        printf("Time to eat = %d\n", data->time_to_eat);
        printf("Time to sleep = %d\n", data->time_to_sleep);

        while (i < data->num_philos)
        {
            //printf("Entra?");
            data->philo[i].seat = i + 1;
            data->philo[i].state = thinking;
            //printf("stato philosopher = %d\n", philo[i].state);
            data->forks[i] = TABLE;
            data->philo[i].left_fork = i % data->num_philos;
            data->philo[i].right_fork = (i + 1) % data->num_philos;
            printf("Valore left fork = %d\n",  data->philo[i].left_fork);
            printf("Valore right fork = %d\n",  data->philo[i].right_fork);
            pthread_create(&data->philo[i].philo_thread, NULL, &philo_routine, &data->philo[i]);
            ++i;
        }
        i = 0; 

        while (i < data->num_philos)
        {
            pthread_join(data->philo[i].philo_thread, NULL);
            printf("Philosopher %d thread ended\n", data->philo[i].seat);
            i++;
        }

    }
}