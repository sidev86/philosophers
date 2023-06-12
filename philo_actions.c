#include "philosopher.h"


void    take_forks_odd(t_philos *philo)
{
        time_t actual_time; 

        actual_time = ft_get_time();
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(philo->output_lock);
        printf("%ld %d has taken a fork\n",(actual_time - philo->initial_time),  philo->philo_id);
        printf("%ld %d has taken a fork\n",(actual_time - philo->initial_time),  philo->philo_id);
        pthread_mutex_unlock(philo->output_lock);
}

void    take_forks(t_philos *philo)
{
        time_t actual_time; 

        actual_time = ft_get_time();
        if (philo ->num_philos == 1)
        {
                pthread_mutex_lock(philo->left_fork);
                pthread_mutex_lock(philo->output_lock);
                printf("%ld %d has taken a fork\n",(actual_time - philo->initial_time),  philo->philo_id);
                pthread_mutex_unlock(philo->output_lock);
                usleep(philo->time_survive * 1000);
        }
        else if (philo->philo_id % 2 == 0 && philo->philo_id != philo->num_philos)
        {
                pthread_mutex_lock(philo->right_fork);
                pthread_mutex_lock(philo->left_fork);
                pthread_mutex_lock(philo->output_lock);
                printf("%ld %d has taken a fork\n",(actual_time - philo->initial_time),  philo->philo_id);
                printf("%ld %d has taken a fork\n",(actual_time - philo->initial_time),  philo->philo_id);
                pthread_mutex_unlock(philo->output_lock);
        }
        else 
                take_forks_odd(philo);
      
}

void    eating_meal(t_philos *philo)
{
        time_t actual_time; 

        actual_time = ft_get_time();
        if (philo->num_philos > 1)
        {
                 pthread_mutex_lock(philo->output_lock);
                printf("%ld %d is eating\n",(actual_time - philo->initial_time),  philo->philo_id);
                pthread_mutex_unlock(philo->output_lock);
                philo->last_meal_time = ft_get_time();
                if (philo->data_table->num_meals != -1)
                        philo->meals_took += 1; 
                usleep(philo->time_to_eat * 1000);
                pthread_mutex_unlock(philo->left_fork);
                pthread_mutex_unlock(philo->right_fork);
        }  
}

void    sleeping(t_philos *philo)
{
        time_t actual_time; 

        if (philo->num_philos > 1)
        {
                actual_time = ft_get_time();
                pthread_mutex_lock(philo->output_lock);
                printf("%ld %d is sleeping\n",(actual_time - philo->initial_time),  philo->philo_id);
                pthread_mutex_unlock(philo->output_lock);
                usleep(philo->time_to_sleep * 1000);
        }
        

}

void    thinking(t_philos *philo)
{
        time_t actual_time; 

        if (philo->num_philos > 1)
        {
                actual_time = ft_get_time();
                pthread_mutex_lock(philo->output_lock);
                printf("%ld %d is thinking\n",(actual_time - philo->initial_time),  philo->philo_id);
                pthread_mutex_unlock(philo->output_lock);
        }
}