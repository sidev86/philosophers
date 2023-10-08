#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;
	t_philo	*philo;

	table = 0;
	philo = 0;
	if (check_args(argc, argv))
		return (1);
	if (init_table(argc, argv, &table))
	{
		print_error(ERR_ON_MALLOC);
		return (1);
	}
	if (init_philos(&philo, &table))
	{
		print_error(ERR_ON_MALLOC);
		return (1);
	}
	if (table->num_philos > 1 && init_mutexes(&table))
	{
		print_error(ERR_MUTEX_INIT);
		return (1);
	}
	start_threads(&philo, &table);
	finish_threads(&philo, &table);
	return (0);
}
