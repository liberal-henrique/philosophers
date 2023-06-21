/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:53:18 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/21 17:04:11 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*start_routine(t_philos	*philo)
{
	pthread_mutex_lock(&philo->mutex_meal);
	philo->last_action = get_time();
	pthread_mutex_unlock(&philo->mutex_meal);
	while (check_printable())
	{
		eating(philo);
		if (!philo->thinking)
		{
			philo->thinking = 1;
			message(philo, THINK);
		}
	}
	return (philo);
}

void	init_routine(t_philos *list)
{
	t_philos	*tmp;

	tmp = list;
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
	init_table(list);
	tmp = list;
	while (tmp)
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
		if (table()->begin == tmp)
			break ;
	}
}

void	supervision(t_philos *philo)
{
	t_philos	*tmp;
	int			counter;
	int			n_philos;

	tmp = philo;
	counter = 0;
	n_philos = table()->n_philos;
	while (check_printable())
	{
		if (!check_hunger(philo))
		{
			pthread_mutex_lock(&table()->print);
			table()->printing = false;
			pthread_mutex_unlock(&table()->print);
			kill_philo(philo);
		}
		pthread_mutex_lock(&table()->print);
		if (philo->n_meals == table()->full)
			counter += 1;
		pthread_mutex_unlock(&table()->print);
	}
}

void	init_table(t_philos *philo)
{
	pthread_create(&table()->thread, NULL, (void *) supervision, philo);
	pthread_join(table()->thread, NULL);
}

void	destroy_philos_list(t_philos *list)
{
	t_philos	*stop;
	t_philos	*tmp;

	stop = list;
	while (list)
	{
		tmp = list->next;
		if (tmp == stop)
			break ;
		pthread_mutex_destroy(&list->utensils.mutex);
		pthread_mutex_destroy(&list->mutex_meal);
		pthread_mutex_destroy(&list->mutex_life);
		pthread_mutex_destroy(&table()->print);
		free(list);
		list = tmp;
	}
	free(list);
}
