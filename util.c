/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:47:46 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/21 17:19:32 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	ft_atoi(const char *str)
{
	int	res;
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	res = 0;
	if (!str)
		return (0);
	while (is_space(str[i]))
		i++;
	sign = (str[i] != '-') - (str[i] == '-');
	i += (str[i] == '-' || str[i] == '+');
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

void	msg(t_philos *philo, int code, t_ulong time)
{
	if (code == EAT)
		printf("%.5lu %i is eating\n", time, philo->id);
	else if (code == THINK)
		printf("%.5lu %i is thinking\n", time, philo->id);
	else if (code == SLEEP)
		printf("%.5lu %i is sleeping\n", time, philo->id);
	else if (code == FORK)
		printf("%.5lu %i is has taken a fork\n", time, philo->id);
	else if (code == DEAD)
		printf("%.5lu %i is died\n", time, philo->id);
}

void	message(t_philos *philo, int code)
{
	t_ulong	time;

	time = get_time() - table()->start_time;
	pthread_mutex_lock(&philo->mutex_meal);
	philo->last_action = get_time();
	pthread_mutex_unlock(&philo->mutex_meal);
	pthread_mutex_lock(&table()->print);
	if (table()->printing == true)
	{
		msg(philo, code, time);
	}
	pthread_mutex_unlock(&table()->print);
	if (table()->times[code] > 0)
		ft_usleep(philo, table()->times[code]);
}
