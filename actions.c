/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:25:32 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/21 16:22:45 by lliberal         ###   ########.fr       */
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
	if (check_alive(philo) && take_forks(philo))
	{
		philo->thinking = 0;
		pthread_mutex_lock(&philo->mutex_meal);
		philo->last_meal = get_time() + table()->times[DEAD];
		pthread_mutex_unlock(&philo->mutex_meal);
		message(philo, EAT);
		pthread_mutex_lock(&table()->print);
		philo->n_meals += 1;
		pthread_mutex_unlock(&table()->print);
		if (philo->id % 2 == 0)
			give_fork(&philo->next->utensils, &philo->utensils);
		else
			give_fork(&philo->utensils, &philo->next->utensils);
		message(philo, SLEEP);
		message(philo, THINK);
	}
}

void	kill_philo(t_philos *philo)
{
	pthread_mutex_lock(&philo->mutex_life);
	philo->alive = false;
	pthread_mutex_unlock(&philo->mutex_life);
}
