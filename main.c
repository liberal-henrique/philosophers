/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:38:22 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/17 14:18:56 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

// number_of_philosophers time_to_die time_to_eat time_to_sleep
// [number_of_times_each_philosopher_must_eat]

int	main(int ac, char **av)
{
	if (check_input(ac, av) < 0)
		return (1);
	philo_list(10);
	print_list(table()->begin);
	destroy_philos_list(table()->begin);
	return (0);
}
