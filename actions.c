/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:25:32 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/30 10:30:13 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	eating(t_philos *philo)
{
	choose_fork(philo);
	philo->status = EAT;
	philo->last_meal = get_time();
	philo->n_meals++;
	message(philo, EAT);
	give_fork(&philo->utensils, &philo->next->utensils);
}

void	thinking(t_philos *philo)
{
	if (philo->status != THINK)
	{
		philo->status = THINK;
		message(philo, THINK);
	}
}
