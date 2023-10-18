/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sibrahim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:26:34 by sibrahim          #+#    #+#             */
/*   Updated: 2023/10/09 09:26:36 by sibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *msg)
{
	printf("Error: %s\n", msg);
	printf("\nUsage: ./philo [number_of_philosophers] [time_to_die] \
	[time_to_eat] [time_to_sleep] [number_of_meals(OPTIONAL)]\n");
	printf("Time to die, eat and sleep are considered in milliseconds (ms)\n");
}
