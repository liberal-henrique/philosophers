/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:53:18 by lliberal          #+#    #+#             */
/*   Updated: 2023/07/03 14:06:45 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	start_routine(t_philos	*philo)
{
	philo->last_meal = get_time();
	if (philo->id % 2)
		usleep(250);
	while (check_alive(philo))
	{
		eating(philo);
		message(philo, SLEEP);
	}
}

void	init_routine(t_philos *philos)
{
	t_philos	*tmp;

	tmp = philos;
	table()->start_time = get_time();
	while (tmp)
	{
		pthread_create(&tmp->thread, NULL, (void *)start_routine, tmp);
		tmp = tmp->next;
		if (table()->begin == tmp)
			break ;
	}
	init_table(tmp);
	start_join(philos);
}

void	start_join(t_philos *philo)
{
	while (philo)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		if (table()->begin == philo)
			break ;
	}
}

void	supervision(t_philos *philo)
{
	int	counter_full;

	(void)philo;
	counter_full = 0;
	set_all(philo, ALIVE);
	while (1)
	{
		pthread_mutex_lock(&philo->mutex_life);
		if (philo->alive == DEAD || counter_full == table()->n)
		{
			pthread_mutex_unlock(&philo->mutex_life);
			set_all(philo, DEAD);
			return ;
		}
		if (philo->alive == FULL)
			counter_full++;
		else if (philo->alive != FULL)
			counter_full = 0;
		pthread_mutex_unlock(&philo->mutex_life);
		philo = philo->next;
	}
}
