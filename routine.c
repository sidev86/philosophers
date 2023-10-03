#include "philo.h"

void	ft_msleep(int time)
{
	long long	tmp;

	tmp = get_current_time() + time;
	while (get_current_time() < tmp)
		usleep(100);
}

void	print_state(t_philo *philo, char *state)
{
	long int	actual_time;

	actual_time = get_current_time() - philo->table->start_time;
	pthread_mutex_lock(&philo->table->print_out);
	if (!ft_strncmp(state, "takefork", 8))
		printf("%ldms %d is taking a fork\n", actual_time, philo->philo_number);
	else if (!ft_strncmp(state, "eat", 3))
		printf("%ldms %d is eating\n", actual_time, philo->philo_number);
	else if (!ft_strncmp(state, "sleep", 5))
		printf("%ldms %d is sleeping\n", actual_time, philo->philo_number);
	else if (!ft_strncmp(state, "thinking", 8))
		printf("%ldms %d is thinking\n", actual_time, philo->philo_number);
	else if (!ft_strncmp(state, "die", 3))
		printf("%ldms %d died\n", actual_time, philo->philo_number);
	else if (!ft_strncmp(state, "alleat", 7))
		printf("all philos ate %d times. stop\n", philo->table->num_of_meals);
	pthread_mutex_unlock(&philo->table->print_out);
}

void	routine_thread(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	philo->fork_right = &philo->table->forks[philo->philo_number - 1];
	philo->fork_left = &philo->table->forks \
	[philo->philo_number % philo->table->num_philos];
	if (philo->philo_number % 2 == 0)
		usleep(15000);
	while (!philo->table->some_die && !philo->eat_all_meals)
	{
		pthread_mutex_lock(philo->fork_left);
		print_state(philo, "takefork");
		pthread_mutex_lock(philo->fork_right);
		print_state(philo, "takefork");
		print_state(philo, "eat");
		philo->last_meal = get_current_time();
		//printf("last meal time : %ld\n", philo->last_meal);
		//printf("start time : %ld\n", philo->table->start_time);
		ft_msleep(philo->table->time_to_eat);
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		philo->meals_eaten++;
		if (philo->meals_eaten == philo->table->num_of_meals)
			philo->eat_all_meals = 1;
		if (philo->eat_all_meals)
			break ;
		print_state(philo, "sleep");
		ft_msleep(philo->table->time_to_sleep);
		print_state(philo, "thinking");
	}
}
