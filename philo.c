/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:53:07 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/20 12:32:27 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

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

t_philos	*philo_list(int num)
{
	t_philos	*philo;
	t_philos	*philo_end;
	int			i;

	i = 0;
	table()->begin = NULL;
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
	if (philo_end && philo_end != table()->begin)
		philo_end->next = table()->begin;
	return (table()->begin);
}

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
