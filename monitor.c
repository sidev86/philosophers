#include "philo.h"

static int	check_philos_eat_all(t_philo *philo)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < philo->table->num_philos)
	{
		if (philo[i].eat_all_meals)
			count++;
		i++;
	}
	if (count == philo->table->num_philos)
	{
		philo->table->all_philos_eat = 1;
		return (1);
	}
	return (0);
}

static int	check_lastmeal_time(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->table->last_meal_lock);
	if (get_current_time() - philo[i].last_meal > philo->table->time_to_die)
	{
		//printf("last meal time %ld\n", philo[i].last_meal);
		//printf("start time %ld\n", philo->table->start_time);
		//printf("time passed since start time 
		//%ld\n", get_current_time() - philo->table->start_time);
		//printf("time passed since last meal time 
		//%ld\n", get_current_time() - philo[i].last_meal);
		philo->table->some_die = 1; 
		
	}
	pthread_mutex_unlock(&philo->table->last_meal_lock);
	return (0);
}

static void print_result(t_philo *philo, char *state)
{
	long int	actual_time;
	
	actual_time = get_current_time() - philo->table->start_time;
	pthread_mutex_lock(&philo->table->print_out);
	if (!ft_strncmp(state, "die", 3))
		printf("%ldms %d died\n", actual_time, philo->philo_number);
	else if (!ft_strncmp(state, "alleat", 7))
		printf("all philos ate %d times. stop\n", philo->table->num_of_meals);
	pthread_mutex_unlock(&philo->table->print_out);	
}

void	monitor_thread(void *ph)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *) ph;
	while (!philo->table->some_die && !philo->table->all_philos_eat)
	{
		i = 0;
		
		while (i < philo->table->num_philos)
		{
			if (check_lastmeal_time(philo, i))
				break ;
			if (check_philos_eat_all(philo))
				break ;
			i++;
		}
		if (philo->table->all_philos_eat)
		{
			print_result(philo, "alleat");
			finish_threads(&philo, &philo->table);
		}
		if (philo->table->some_die)
		{
			print_result(philo, "die");
			finish_threads(&philo, &philo->table);
		}	
	}
}
