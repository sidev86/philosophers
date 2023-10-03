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
	if (get_current_time() - philo[i].last_meal > philo->table->time_to_die)
	{
		//printf("last meal time %ld\n", philo[i].last_meal);
		//printf("start time %ld\n", philo->table->start_time);
		//printf("time passed since start time 
		//%ld\n", get_current_time() - philo->table->start_time);
		//printf("time passed since last meal time 
		//%ld\n", get_current_time() - philo[i].last_meal);
		philo->table->some_die = 1;
		return (1);
	}
	return (0);
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
			print_state(philo, "alleat");
			exit(1);
		}
		if (philo->table->some_die)
		{
			print_state(philo, "die");
			exit(1);
		}
	}
}
