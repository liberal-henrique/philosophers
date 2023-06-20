/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:23:41 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/20 12:38:55 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

bool	take_fork(t_philos *philo, t_fork *first, t_fork *second)
{
	bool	got;

	got = false;
	pthread_mutex_lock(&first->mutex);
	if (first->fork)
	{
		pthread_mutex_lock(&second->mutex);
		if (second->fork)
		{
			got = true;
			first->fork = false;
			msg(philo, FORK);
			second->fork = false;
			msg(philo, FORK);
		}
		pthread_mutex_unlock(&second->mutex);
	}
	pthread_mutex_unlock(&first->mutex);
	return (got);
}

void	msg(t_philos *philo, int code)
{
	t_ulong	time;

	time = get_time() - table()->start_time;
	philo->last_action = get_time();
	if (code == EAT)
		printf("%.5lu Philo %i is eating\n", time, philo->id);
	else if (code == THINK)
		printf("%.5lu Philo %i is thinking\n", time, philo->id);
	else if (code == SLEEP)
		printf("%.5lu Philo %i is sleeping\n", time, philo->id);
	else if (code == FORK)
		printf("%.5lu Philo %i has taken a fork\n", time, philo->id);
	if (table()->times[code] > 0)
		ft_usleep(philo, table()->times[code]);
}
