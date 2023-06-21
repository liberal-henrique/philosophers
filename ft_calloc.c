/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:58:06 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/21 10:49:57 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*ft_calloc(size_t length)
{
	void				*tmp;
	unsigned char		*element;

	if (length < 1)
		return (NULL);
	tmp = malloc(length);
	if (!tmp)
		return (NULL);
	element = (unsigned char *)tmp;
	while (length-- > 0)
	{
		*element = 0;
		element++;
	}
	return (tmp);
}

// int	put_nbr(int num)
// {
// 	char	s[10] = "0123456789";

// 	if (num > 9)
// 		put_nbr(num / 10);
// 	return (write(1, &s[num % 10], 1));
// }
