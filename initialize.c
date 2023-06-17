/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:53:18 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/17 15:46:39 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	print_list(t_philos *list)
{
	while (list)
	{
		printf("[%i", list->id);
		printf("]--->");
		list = list->next;
		if (list == table()->begin)
			break ;
	}
	printf("\n");
}

void	init_routine(t_philos *list)
{
	t_philos	*tmp;

	tmp = list;
	while (tmp)
	{
		if (table()->begin == tmp)
			break ;
		pthread_create(&tmp->thread, NULL, NULL, NULL);
		tmp = tmp->next;
	}
}

t_philos	*create_philo(int i)
{
	t_philos	*new;

	new = malloc_ob(sizeof(t_philos));
	new->id = i;
	new->last_meal = 0;
	new->fork.fork = true;
	pthread_mutex_init(&new->fork.mutex, NULL);
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
		pthread_mutex_destroy(&list->fork.mutex);
		pthread_mutex_destroy(&list->mutex_meal);
		pthread_mutex_destroy(&list->mutex_life);
		free(list);
		list = tmp;
	}
	free(list);
}
