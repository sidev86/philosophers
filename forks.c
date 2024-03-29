/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:25:42 by sibrahim          #+#    #+#             */
/*   Updated: 2023/10/09 09:25:44 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->philo_number == philo->table->num_philos)
	{
		pthread_mutex_lock(philo->fork_left);
		print_state(philo, "takefork");
		pthread_mutex_lock(philo->fork_right);
		print_state(philo, "takefork");
	}
	else
	{
		pthread_mutex_lock(philo->fork_right);
		print_state(philo, "takefork");
		pthread_mutex_lock(philo->fork_left);
		print_state(philo, "takefork");
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->philo_number == philo->table->num_philos)
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
	}
	else
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
	}
}
