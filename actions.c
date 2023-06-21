/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:25:32 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/21 11:04:16 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

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
		message(philo, EAT);
		if (philo->id % 2 == 0)
			give_fork(&philo->next->utensils, &philo->utensils);
		else
			give_fork(&philo->utensils, &philo->next->utensils);
		message(philo, SLEEP);
		message(philo, THINK);
	}
}

bool	kill_philo(t_philos *philo)
{
	pthread_mutex_lock(&philo->mutex_life);
	philo->alive = false;
	pthread_mutex_unlock(&philo->mutex_life);
	return (philo->alive);
}

bool	check_alive(t_philos *philo)
{
	pthread_mutex_lock(&philo->mutex_life);
	if (philo->alive)
	{
		pthread_mutex_unlock(&philo->mutex_life);
		return (true);
	}
	pthread_mutex_unlock(&philo->mutex_life);
	return (false);
}

bool	check_hunger(t_philos *philo)
{
	pthread_mutex_lock(&philo->mutex_meal);
	if (get_time() - philo->last_meal - table()->times[DEAD] <= 0)
	{
		philo->alive = false;
		return (false);
	}
	pthread_mutex_unlock(&philo->mutex_meal);
	return (true);
}
