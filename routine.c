/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:23:41 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/30 10:29:57 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

bool	choose_fork(t_philos *philo)
{
	if (philo->id % 2)
	{
		return (take_fork(philo, &philo->next->utensils), \
		+ take_fork(philo, &philo->utensils));
	}
	return (take_fork(philo, &philo->utensils)
		+ take_fork(philo, &philo->next->utensils));
}

bool	take_fork(t_philos *philo, t_fork *fork)
{
	bool	got;

	got = false;
	while (!got && check_alive(philo))
	{
		pthread_mutex_lock(&fork->mutex);
		if (fork->fork)
		{
			got = true;
			fork->fork = false;
			message(philo, FORK);
			pthread_mutex_unlock(&fork->mutex);
		}
		else
		{
			pthread_mutex_unlock(&fork->mutex);
			thinking(philo);
			usleep(150);
		}
	}
	return (true);
}

bool	return_fork(t_philos *philo)
{
	if (philo->id % 2)
	{
		return (give_fork(&philo->utensils, &philo->next->utensils));
	}
	return (give_fork(&philo->next->utensils, &philo->utensils));
}

bool	give_fork(t_fork *first, t_fork *second)
{
	pthread_mutex_lock(&first->mutex);
	first->fork = true;
	pthread_mutex_unlock(&first->mutex);
	pthread_mutex_lock(&second->mutex);
	second->fork = true;
	pthread_mutex_unlock(&second->mutex);
	return (true);
}
