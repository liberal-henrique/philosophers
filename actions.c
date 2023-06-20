/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:25:32 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/20 13:02:28 by lliberal         ###   ########.fr       */
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

void	give_fork(t_fork *first, t_fork *second)
{
	pthread_mutex_lock(&first->mutex);
	first->fork = true;
	pthread_mutex_unlock(&first->mutex);
	pthread_mutex_lock(&second->mutex);
	second->fork = true;
	pthread_mutex_unlock(&second->mutex);
}

void	eating(t_philos	*philo)
{
	if (!check_alive(philo) && take_forks(philo))
	{
		philo->thinking = 0;
		philo->last_meal = get_time() + table()->times[DEAD];
		msg(philo, EAT);
		if (philo->id % 2 == 0)
			give_fork(&philo->next->utensils, &philo->utensils);
		else
			give_fork(&philo->utensils, &philo->next->utensils);
		msg(philo, SLEEP);
		msg(philo, THINK);
	}
}
