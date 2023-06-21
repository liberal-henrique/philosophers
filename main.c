/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:38:22 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/21 10:35:31 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

// number_of_philosophers time_to_die time_to_eat time_to_sleep
// [number_of_times_each_philosopher_must_eat]

int	main(int ac, char **av)
{
	if (check_input(ac, av) < 0)
		return (1);
	table()->times[DEAD] = ft_atoi(av[2]);
	table()->times[EAT] = ft_atoi(av[3]);
	table()->times[SLEEP] = ft_atoi(av[4]);
	if (av[5])
		table()->full = ft_atoi(av[5]);
	else
		table()->full = INT_MAX;
	philo_list(ft_atoi(av[1]));
	init_routine(table()->begin);
	destroy_philos_list(table()->begin);
	return (0);
}
