/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:53:18 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/20 13:02:07 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*start_routine(t_philos	*philo)
{
	philo->last_action = get_time();
	while (1)
	{
		eating(philo);
		if (!philo->thinking)
		{
			philo->thinking = 1;
			msg(philo, THINK);
		}
	}
	return (philo);
}

void	init_routine(t_philos *list)
{
	t_philos	*tmp;

	tmp = list;
	table()->start_time = get_time();
	while (tmp)
	{
		pthread_create(&tmp->thread, NULL, (void *)start_routine, tmp);
		tmp = tmp->next;
		if (table()->begin == tmp)
			break ;
	}
	tmp = list;
	while (tmp)
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
		if (table()->begin == tmp)
			break ;
	}
}

t_philos	*create_philo(int i)
{
	t_philos	*new;

	new = malloc_ob(sizeof(t_philos));
	new->id = i;
	new->utensils.fork = true;
	pthread_mutex_init(&new->utensils.mutex, NULL);
	pthread_mutex_init(&new->mutex_meal, NULL);
	pthread_mutex_init(&new->mutex_life, NULL);
	new->next = NULL;
	return (new);
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
		free(list);
		list = tmp;
	}
	free(list);
}
