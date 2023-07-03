/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:53:07 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/30 10:03:26 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

t_table	*table(void)
{
	static t_table	table;

	return (&table);
}

t_philos	*create_philo(int i)
{
	t_philos	*new;

	new = ft_calloc(sizeof(t_philos));
	new->id = i;
	new->utensils.fork = true;
	new->alive = DEAD;
	new->n_meals = 0;
	pthread_mutex_init(&new->utensils.mutex, NULL);
	pthread_mutex_init(&new->mutex_life, NULL);
	new->next = NULL;
	return (new);
}

void	destroy_philos_list(t_philos *list)
{
	t_philos	*stop;
	t_philos	*tmp;

	stop = list;
	pthread_mutex_destroy(&table()->print);
	while (list)
	{
		tmp = list->next;
		if (tmp == stop)
			break ;
		pthread_mutex_destroy(&list->utensils.mutex);
		pthread_mutex_destroy(&list->mutex_life);
		free(list);
		list = tmp;
	}
	free(list);
}

void	init_table(t_philos *philo)
{
	pthread_create(&table()->thread, NULL, (void *)supervision, philo);
	pthread_join(table()->thread, NULL);
}

t_philos	*philo_list(int num)
{
	t_philos	*philo;
	t_philos	*philo_end;
	int			i;

	i = 0;
	table()->begin = NULL;
	pthread_mutex_init(&table()->print, NULL);
	philo_end = NULL;
	while (i++ < num)
	{
		philo = create_philo(i);
		if (table()->begin == NULL)
			table()->begin = philo;
		else
			philo_end->next = philo;
		philo_end = philo;
	}
	philo_end->next = table()->begin;
	return (table()->begin);
}
