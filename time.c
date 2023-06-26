/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:49:49 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/23 14:05:30 by lliberal         ###   ########.fr       */
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

void	ft_usleep(int time)
{
	t_ulong	end;

	end = get_time() + time;
	while (get_time() < end)
	{
		usleep(200);
	}
}

bool	calc_time_meal(t_philos *philo)
{
	if (get_time() - philo->last_meal <= 2 * table()->times[EAT])
		return (true);
	return (false);
}
