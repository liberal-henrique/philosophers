/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:53:18 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/23 16:28:31 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	start_routine(t_philos	*philo)
{
	pthread_mutex_lock(&philo->mutex_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->mutex_meal);
	while (check_printable())
	{
		if (table()->n_philos != 1 && \
		!(calc_time_meal(philo) && usleep(200)))
			eating_sleeping(philo);
		if (!philo->thinking)
		{
			philo->thinking = 1;
			message(philo, THINK);
		}
	}
}

void	init_routine(t_philos *philos)
{
	t_philos	*tmp;

	tmp = philos;
	table()->start_time = get_time();
	pthread_mutex_lock(&table()->print);
	table()->printing = true;
	pthread_mutex_unlock(&table()->print);
	while (tmp)
	{
		pthread_create(&tmp->thread, NULL, (void *)start_routine, tmp);
		tmp = tmp->next;
		if (table()->begin == tmp)
			break ;
	}
	usleep(250);
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

int	check_full(t_philos *philo)
{
	int			counter;
	int			loop;

	loop = 0;
	counter = 0;
	while (loop <= table()->n_philos)
	{
		pthread_mutex_lock(&table()->print);
		if (philo->n_meals >= table()->full)
			counter++;
		pthread_mutex_unlock(&table()->print);
		philo = philo->next;
		loop++;
	}
	return (counter);
}

void	supervision(t_philos *philo)
{
	t_philos	*tmp;
	int			n_philos;

	tmp = philo;
	n_philos = table()->n_philos;
	while (check_printable())
	{
		if (!check_hunger(philo))
		{
			pthread_mutex_lock(&table()->print);
			table()->printing = false;
			pthread_mutex_unlock(&table()->print);
			msg(philo, DEAD, get_program_time());
		}
		if (table()->n_philos != INT_MAX && \
		check_full(philo) >= table()->n_philos)
		{
			pthread_mutex_lock(&table()->print);
			table()->printing = false;
			pthread_mutex_unlock(&table()->print);
		}
		philo = philo->next;
	}
}
