/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:47:46 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/17 12:50:22 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

t_table	*table(void)
{
	static t_table	table;

	return (&table);
}

int	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

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
		return (1 - write(2, "You should inform: number of philosophers, \
		time to die, time to eat, time to sleep\n", 83));
	return (0);
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
