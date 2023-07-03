/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 13:10:52 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/30 11:03:09 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	check_input(int ac, char **input)
{
	if (ft_atoi(input[1]) < 1)
		return (1 - write(2, "not enough philosophers\n", 24));
	if (ft_atoi(input[2]) <= 0)
		return (1 - write(2, "not enough time to die\n", 23));
	else if (ft_atoi(input[3]) <= 0)
		return (1 - write(2, "not enough time to eat\n", 23));
	else if (ft_atoi(input[4]) <= 0)
		return (1 - write(2, "not enough time to sleep\n", 25));
	else if (ac < 5 || ac > 6)
		return (1 - write(2, \
	"You should inform: philosophers, time_die, time_eat, time_sleep\n", 65));
	return (0);
}

int	check_num(char **input)
{
	int	i;
	int	j;

	i = 0;
	while (input[++i])
	{
		j = 0;
		while (input[i][j])
		{
			if ((input[i][j] != '+') && !ft_is_num(input[i][j]))
			{
				printf("Invalid arguments\n");
				return (1);
			}
			j++;
		}
	}
	return (0);
}

bool	check_alive(t_philos *philo)
{
	pthread_mutex_lock(&philo->mutex_life);
	if (philo->alive != DEAD)
	{
		if ((get_time() - philo->last_meal) > table()->times[DEAD])
		{
			philo->alive = DEAD;
			pthread_mutex_unlock(&philo->mutex_life);
			msg(philo, DEAD);
			return (false);
		}
		if (philo->n_meals == table()->full)
		{
			philo->alive = FULL;
		}
		pthread_mutex_unlock(&philo->mutex_life);
		return (true);
	}
	pthread_mutex_unlock(&philo->mutex_life);
	return (false);
}

void	set_all(t_philos *philo, int status)
{
	int			loop;

	loop = 0;
	while (loop < table()->n)
	{
		pthread_mutex_lock(&philo->mutex_life);
		philo->alive = status;
		pthread_mutex_unlock(&philo->mutex_life);
		philo = philo->next;
		loop++;
	}
}
