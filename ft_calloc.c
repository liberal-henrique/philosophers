/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:58:06 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/17 12:50:08 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	*malloc_ob(size_t length)
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
