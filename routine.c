/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:26:20 by sibrahim          #+#    #+#             */
/*   Updated: 2023/10/09 09:26:22 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	usleep(100);
	pthread_mutex_lock(&philo->table->death_lock);
	if (!philo->table->some_die)
	{
		if (!ft_strncmp(state, "takefork", 8))
			printf("%ldms %d has taken a fork\n", \
			actual_time, philo->philo_number);
		else if (!ft_strncmp(state, "eat", 3))
			printf("%ldms %d is eating\n", actual_time, philo->philo_number);
		else if (!ft_strncmp(state, "sleep", 5))
			printf("%ldms %d is sleeping\n", actual_time, philo->philo_number);
		else if (!ft_strncmp(state, "thinking", 8))
			printf("%ldms %d is thinking\n", actual_time, philo->philo_number);
	}
	pthread_mutex_unlock(&philo->table->death_lock);
}

void	onephilo_thread(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	printf("%ldms %d has taken a fork\n", \
	get_current_time() - philo->table->start_time, philo->philo_number);
	usleep(philo->table->time_to_die * 1000);
	printf("%ldms %d died\n", \
	(get_current_time() - philo->table->start_time) + 1, philo->philo_number);
}

int	philo_states(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->death_lock);
	take_forks(philo);
	print_state(philo, "eat");
	pthread_mutex_lock(&philo->table->last_meal_lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->table->last_meal_lock);
	ft_msleep(philo->table->time_to_eat);
	drop_forks(philo);
	pthread_mutex_lock(&philo->table->meals_lock);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->table->num_of_meals)
		philo->eat_all_meals = 1;
	pthread_mutex_unlock(&philo->table->meals_lock);
	if (philo->eat_all_meals)
		return (1);
	print_state(philo, "sleep");
	ft_msleep(philo->table->time_to_sleep);
	print_state(philo, "thinking");
	pthread_mutex_lock(&philo->table->death_lock);
	return (0);
}

void	routine_thread(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	philo->fork_left = &philo->table->forks[philo->philo_number - 1];
	philo->fork_right = \
	&philo->table->forks[philo->philo_number % philo->table->num_philos];
	if (philo->philo_number % 2 == 0)
		ft_msleep(100);
	pthread_mutex_lock(&philo->table->death_lock);
	while (!philo->table->some_die)
	{
		if (philo_states(philo))
			break ;
	}
	if (!philo->eat_all_meals)
		pthread_mutex_unlock(&philo->table->death_lock);
}
