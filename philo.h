/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:03:18 by lliberal          #+#    #+#             */
/*   Updated: 2023/06/23 15:33:59 by lliberal         ###   ########.fr       */
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

# define DEAD		0
# define EAT		1
# define THINK		2
# define SLEEP		3
# define FORK		4

# define H printf("Here\n");

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
	int				n_meals;
	bool			alive;
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
	int				full;
	int				n_philos;
	t_phmutex		print;
	bool			printing;
	t_ulong			start_time;
	pthread_t		thread;
	t_ulong			times[5];
	t_philos		*begin;
};

//--------philo----------------//
t_table				*table(void);
t_philos			*philo_list(int num);
t_philos			*create_philo(int i);
void				print_list(t_philos *list);
void				destroy_philos_list(t_philos *list);

//--------initialize---------//
void				start_routine(t_philos	*philo);
void				init_routine(t_philos *list);
void				supervision(t_philos *philo);
void				init_table(t_philos *philo);
void				start_join(t_philos *philo);

//---------routine-----------//
bool				take_fork(t_philos *philo, t_fork *first, t_fork *second);
bool				take_forks(t_philos *philo);

//--------check-----------------//
int					check_input(int ac, char **input);
bool				check_hunger(t_philos *philo);
bool				check_printable(void);

//---------util----------------//
int					is_space(char c);
int					ft_atoi(const char *str);
void				msg(t_philos *philo, int code, t_ulong time);
void				message(t_philos *philo, int code);

//---------ft_calloc----------//
void				*ft_calloc(size_t length);
int					put_nbr(int num);

//---------time----------------//
void				ft_usleep(int time);
t_ulong				get_time(void);
t_ulong				get_program_time(void);
bool				calc_time_meal(t_philos *philo);

//--------actions--------------//
void				give_fork(t_fork *first, t_fork *second);
void				eating_sleeping(t_philos	*philo);

#endif
