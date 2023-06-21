/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:03:18 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/21 11:04:48 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<sys/time.h>
# include<unistd.h>
# include<stdio.h>
# include<limits.h>
# include<stdlib.h>
# include<stdbool.h>
# include<pthread.h>

# define DEAD		1
# define EAT		2
# define THINK		3
# define SLEEP		4
# define FORK		5

typedef unsigned long	t_ulong;
typedef pthread_mutex_t	t_phmutex;

typedef struct s_table	t_table;
typedef struct s_philos	t_philos;
typedef struct s_fork	t_fork;

struct s_fork
{
	t_phmutex		mutex;
	bool			fork;
};

struct s_philos
{
	int				id;
	bool			alive;
	int				n_meals;
	bool			thinking;
	pthread_t		thread;
	t_ulong			last_action;
	t_ulong			last_meal;
	t_phmutex		mutex_life;
	t_phmutex		mutex_meal;
	t_fork			utensils;
	t_philos		*next;
};

struct	s_table
{
	t_ulong			start_time;
	int				full;
	pthread_t		thread;
	t_ulong			times[5];
	t_philos		*begin;
};

//--------philo----------------//
bool				kill_philo(t_philos *philo);
bool				check_alive(t_philos *philo);
t_philos			*philo_list(int num);
void				print_list(t_philos *list);

//--------initialize---------//
void				*start_routine(t_philos	*philo);
void				init_routine(t_philos *list);
t_philos			*create_philo(int i);
void				destroy_philos_list(t_philos *list);

//---------routine-----------//
void				give_fork(t_fork *first, t_fork *second);
bool				take_fork(t_philos *philo, t_fork *first, t_fork *second);
bool				take_forks(t_philos *philo);
void				msg(t_philos *philo, int code, t_ulong time);
void				message(t_philos *philo, int code);
void				eating(t_philos	*philo);

//---------util----------------//
t_table				*table(void);
int					is_space(char c);
int					check_input(int ac, char **input);
int					ft_atoi(const char *str);

//---------ft_calloc----------//
void				*ft_calloc(size_t length);
int					put_nbr(int num);

//---------time----------------//
t_ulong				get_time(void);
void				ft_usleep(t_philos	*philo, int milisecs);
t_ulong				get_program_time(void);

//--------actions--------------//
bool				check_hunger(t_philos *philo);

#endif
