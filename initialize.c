/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:53:18 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/21 11:07:58 by lliberal         ###   ########.fr       */
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
			message(philo, THINK);
		}
	}
	return (philo);
}

// void	supervision(t_philos *philo)
// {
// 	t_philos	*tmp;

// 	tmp = philo;
// 	while (1)
// 	{
// 		if (!check_hunger)
// 			kill_philo(philo);
// 		tmp = tmp->next;
// 	}
// }

// void	init_table(t_philos *philo)
// {
// 	pthread_create(&table()->thread, NULL, (void *) supervision, philo);
// 	pthread_join(table()->thread, NULL);
// }

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
