/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:23:41 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/23 13:17:27 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

bool	take_forks(t_philos *philo)
{
	if (philo->id % 2 == 0)
	{
		return (take_fork(philo, &philo->next->utensils, \
		&philo->utensils));
	}
	return (take_fork(philo, &philo->utensils, &philo->next->utensils));
}

bool	take_fork(t_philos *philo, t_fork *first, t_fork *second)
{
	bool	got;

	got = false;
	pthread_mutex_lock(&first->mutex);
	if (first->fork)
	{
		pthread_mutex_lock(&second->mutex);
		if (second->fork)
		{
			got = true;
			first->fork = false;
			message(philo, FORK);
			second->fork = false;
			message(philo, FORK);
		}
		pthread_mutex_unlock(&second->mutex);
	}
	pthread_mutex_unlock(&first->mutex);
	return (got);
}
