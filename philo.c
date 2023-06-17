/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:53:07 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/17 12:53:37 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

t_philos	*philo_list(int num)
{
	t_philos	*philo;
	t_philos	*philo_end;
	int			i;

	i = 0;
	table()->begin = NULL;
	philo_end = NULL;
	while (i++ < num)
	{
		philo = create_philo(i);
		if (table()->begin == NULL)
			table()->begin = philo;
		else
			philo_end->next = philo;
		philo_end = philo;
	}
	if (philo_end && philo_end != table()->begin)
		philo_end->next = table()->begin;
	return (table()->begin);
}
