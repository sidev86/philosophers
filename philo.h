/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:26:52 by sibrahim          #+#    #+#             */
/*   Updated: 2023/10/09 09:27:00 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define ERR_NUM_ARGS "Number of arguments invalid. Must be between 5 and 6."
# define ERR_INVALID_ARGS "One or more arguments are not valid."
# define ERR_NUM_PHILOS_ARG "Number of philosophers cannot be more than 200"
# define ERR_MUTEX_INIT "Mutex initialization error"
# define ERR_ON_MALLOC "Memory Allocation Error on Heap with malloc"

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

typedef struct s_table
{
	int				num_philos;
	int				num_of_meals;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				some_die;
	int				all_philos_eat;
	long			start_time;
	pthread_t		monitor_thread;
	pthread_mutex_t	meals_lock;
	pthread_mutex_t	last_meal_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	print_out;
	pthread_mutex_t	forks[250];
}		t_table;

typedef struct s_philo
{
	int				philo_number;
	int				meals_eaten;
	int				eat_all_meals;
	int				is_eating;
	long			last_meal;
	pthread_t		ph_thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_table			*table;
}		t_philo;

int			check_args(int argc, char **argv);
int			init_table(int argc, char **argv, t_table **table);
int			init_philos(t_philo **philo, t_table **table);
int			init_mutexes(t_table **table);
int			ft_atoi(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);
void		print_error(char *msg);
void		start_threads(t_philo **philo, t_table **table);
void		finish_threads(t_philo **philo, t_table **table);
void		routine_thread(void *ph);
void		monitor_thread(void *ph);
void		onephilo_thread(void *ph);
void		print_state(t_philo *philo, char *state);
void		free_data(t_table *table, t_philo *philo);
long		get_current_time(void);
#endif
