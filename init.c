#include "philo.h"

int	init_table(int argc, char **argv, t_table **table)
{
	*table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	(*table)->num_philos = ft_atoi(argv[1]);
	(*table)->time_to_die = ft_atoi(argv[2]);
	(*table)->time_to_eat = ft_atoi(argv[3]);
	(*table)->time_to_sleep = ft_atoi(argv[4]);
	(*table)->num_of_meals = -1;
	(*table)->some_die = 0;
	(*table)->all_philos_eat = 0;
	(*table)->start_time = get_current_time();
	if (argc == 6)
		(*table)->num_of_meals = ft_atoi(argv[5]);
	return (0);
}

int	init_philos(t_philo **philo, t_table **table)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * (*table)->num_philos);
	if (!philo)
		return (1);
	while (i < (*table)->num_philos)
	{
		(*philo)[i].philo_number = i + 1;
		(*philo)[i].meals_eaten = 0;
		(*philo)[i].eat_all_meals = 0;
		(*philo)[i].is_eating = 0;
		(*philo)[i].table = (*table);
		(*philo)[i].last_meal = get_current_time();
		i++;
	}
	return (0);
}

int	init_mutexes(t_table **table)
{
	int	i;

	i = 0;
	while (i < (*table)->num_philos)
	{
		if (pthread_mutex_init(&(*table)->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&(*table)->death_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(*table)->print_out, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(*table)->last_meal_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(*table)->meals_lock, NULL) != 0)
		return (1);
	return (0);
}
