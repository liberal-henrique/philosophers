/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:49:49 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/21 17:03:35 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

t_ulong	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

t_ulong	get_program_time(void)
{
	return (get_time() - table()->start_time);
}

void	ft_usleep(t_philos *philo, int milisecs)
{
	t_ulong	end;

	end = get_time() + milisecs;
	while (get_time() < end)
	{
		if (!check_alive(philo))
		{
			pthread_mutex_lock(&table()->print);
			table()->printing = false;
			pthread_mutex_unlock(&table()->print);
			kill_philo(philo);
		}
		usleep(200);
	}
}
