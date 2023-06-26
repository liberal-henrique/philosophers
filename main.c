/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:38:22 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/23 16:01:17 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

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
	table()->n_philos = ft_atoi(av[1]);
	table()->begin = philo_list(table()->n_philos);
	init_routine(table()->begin);
	destroy_philos_list(table()->begin);
	return (0);
}
