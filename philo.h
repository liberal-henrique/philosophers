/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:03:18 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/17 15:01:43 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<sys/time.h>
# include<unistd.h>
# include<stdio.h>
# include<stdlib.h>
# include<stdbool.h>
# include<pthread.h>

#define H printf("Here\n");

typedef struct s_table	t_table;
typedef struct s_philos	t_philos;
typedef struct s_fork	t_fork;

struct s_fork
{
	pthread_mutex_t	mutex;
	bool			fork;
};

struct s_philos
{
	int				id;
	pthread_mutex_t	mutex_life;
	bool			alive;
	pthread_mutex_t	mutex_meal;
	unsigned long	last_meal;
	t_fork			fork;
	pthread_t		thread;
	t_philos		*next;
};

struct	s_table
{
	unsigned long	start_time;
	unsigned long	death_time;
	unsigned long	sleep_time;
	t_philos		*begin;
};

//---------singleton-----------//
t_table				*table(void);

//--------philo----------------//
void				print_list(t_philos *list);
t_philos			*create_philo(int i);
t_philos			*philo_list(int num);
void				destroy_philos_list(t_philos *list);

//---------util----------------//
int					ft_atoi(const char *str);
void				ft_usleep(int milisecs);
int					check_input(int ac, char **input);
//---------ft_calloc----------//
void				*malloc_ob(size_t length);

#endif
