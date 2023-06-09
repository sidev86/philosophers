#include "philosopher.h"


void    take_forks(t_philos *philo)
{
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(philo->output_lock);
        printf("Philosopher %d has taken a fork\n", philo->philo_id);
        printf("Philosopher %d has taken a fork\n", philo->philo_id);
        pthread_mutex_unlock(philo->output_lock);
}

void    eating_meal(t_philos *philo)
{
        
}

void    sleeping(t_philos *philo)
{

}

void    thinking(t_philos *philo)
{

}