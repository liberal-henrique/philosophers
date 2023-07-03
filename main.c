/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:38:22 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/30 11:00:30 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	main(int ac, char **av)
{
	if (check_num(av))
		return (1);
	if (check_input(ac, av) < 0)
		return (1);
	table()->times[DEAD] = ft_atoi(av[2]);
	table()->times[EAT] = ft_atoi(av[3]);
	table()->times[SLEEP] = ft_atoi(av[4]);
	if (av[5])
	{
		table()->full = ft_atoi(av[5]);
		if (table()->full <= 0)
			return (1);
	}
	else
		table()->full = INT_MAX;
	table()->n = ft_atoi(av[1]);
	if (table()->n <= 0)
		return (1);
	table()->begin = philo_list(table()->n);
	init_routine(table()->begin);
	destroy_philos_list(table()->begin);
	return (0);
}
