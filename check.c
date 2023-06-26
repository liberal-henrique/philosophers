/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:10:52 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/23 14:20:45 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	check_input(int ac, char **input)
{
	if (ft_atoi(input[1]) < 1)
		return (1 - write(2, "not enough philosophers\n", 24));
	else if (ft_atoi(input[2]) < 0)
		return (1 - write(2, "not enough time to die\n", 23));
	else if (ft_atoi(input[3]) < 0)
		return (1 - write(2, "not enough time to eat\n", 23));
	else if (ft_atoi(input[4]) < 0)
		return (1 - write(2, "not enough time to sleep\n", 25));
	else if (ac < 5)
		return (1 - write(2, \
	"You should inform: philosophers, time_die, time_eat, time_sleep\n", 65));
	return (0);
}

bool	check_hunger(t_philos *philo)
{
	pthread_mutex_lock(&philo->mutex_meal);
	if (get_time() - philo->last_meal > table()->times[DEAD])
	{
		pthread_mutex_unlock(&philo->mutex_meal);
		return (false);
	}
	pthread_mutex_unlock(&philo->mutex_meal);
	return (true);
}

bool	check_printable(void)
{
	pthread_mutex_lock(&table()->print);
	if (table()->printing)
	{
		pthread_mutex_unlock(&table()->print);
		return (true);
	}
	pthread_mutex_unlock(&table()->print);
	return (false);
}
