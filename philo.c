#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
 
#define THINK 't'
#define SLEEP 's'
#define EAT 'e'

int *forks; 
pthread_mutex_t mutex; 

typedef struct s_philos
{
    int p;
    int time_to_eat; 
    int time_to_sleep; 
    int time_to_die; 
    int num_forks; 
    char state; 
}               t_philos; 

void*   routine(void *arg)
{
    t_philos *ph = (t_philos*)arg;
    int index = ph->p - 1;
    struct timeval start_time, end_time; 
    long elapsed_time_ms;

    gettimeofday(&start_time, NULL); 
    while (ph->time_to_die != 0)
    {
        if (ph->state == THINK) 
        {
            if (forks[index] == 1 && forks[(index+1) % ph->num_forks] == 1)
            {
                pthread_mutex_lock(&mutex);
                forks[index] = 0;
                forks[(index+1) % ph->num_forks] = 0;
                ph->state = EAT; 
                gettimeofday(&end_time, NULL); 
                elapsed_time_ms = (end_time.tv_sec - start_time.tv_sec) * 1000 + (end_time.tv_usec - start_time.tv_usec) / 1000; 
                printf("%ldms %d is eating\n",elapsed_time_ms, ph->p); 
                pthread_mutex_unlock(&mutex);
                usleep(ph->time_to_eat * 1000);
            }
        }
        else if (ph->state == EAT && forks[index] == 0 && forks[(index+1) % ph->num_forks] == 0)
        {
            pthread_mutex_lock(&mutex);
            forks[index] = 1;
            forks[(index+1) % ph->num_forks] = 1;
            ph->state = SLEEP;
            gettimeofday(&end_time, NULL); 
            elapsed_time_ms = (end_time.tv_sec - start_time.tv_sec) * 1000 + (end_time.tv_usec - start_time.tv_usec) / 1000; 
            printf("%ldms %d is sleeping\n",elapsed_time_ms, ph->p); 
            pthread_mutex_unlock(&mutex);
            usleep(ph->time_to_sleep * 1000);
        }
        else
        {
            if (ph->state == SLEEP)
            {
                ph->state = THINK;
                gettimeofday(&end_time, NULL); 
                elapsed_time_ms = (end_time.tv_sec - start_time.tv_sec) * 1000 + (end_time.tv_usec - start_time.tv_usec) / 1000; 
                printf("%ldms %d is thinking\n",elapsed_time_ms, ph->p); 
            }    
        }
    }
  
    printf("Philosopher %d: Thread Started\n", ph->p);

    return (0); 
}



int main(int argc, char **argv)
{
    int i = 1; 
    int num_ph;
    t_philos *phs; 
    pthread_t *th;
    
    if (argc == 5)
    {
        num_ph = atoi(argv[1]);
        phs = malloc(sizeof(t_philos) * num_ph);
        th = malloc(sizeof(pthread_t) * num_ph); 
        forks = malloc(sizeof(int) * num_ph);
        pthread_mutex_init(&mutex, NULL);
        printf("Number of philosophers = %d\n", num_ph);
        printf("Time to die = %d\n", atoi(argv[2]));
        printf("Time to eat = %d\n", atoi(argv[3]));
        printf("Time to sleep = %d\n", atoi(argv[4]));
        i = 0; 
        while (i < num_ph)
        {
            forks[i] = 1;
            phs[i].p = i+1;
            phs[i].num_forks = num_ph; 
            phs[i].time_to_die = atoi(argv[2]);
            phs[i].time_to_eat = atoi(argv[3]);
            phs[i].time_to_sleep = atoi(argv[4]);
            phs[i].state = THINK;
            if (pthread_create(&th[i], NULL, &routine, &phs[i]) != 0)
                return i;
            //phs[i].has_fork = 1; 
            i++;
        }
        i = 0; 
        sleep(3);
        while (i < num_ph)
        {
            if (pthread_join(th[i], NULL) != 0)
                return i; 
            printf("Philosopher %d: Thread Ended\n", phs[i].p);
            i++;
        }
        pthread_mutex_destroy(&mutex);

    }
    else 
        printf("Wrong number of arguments\n");

}