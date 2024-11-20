/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:05:21 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/07/30 15:28:14 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

/*
 *	Define
 */

# define E_USAGE	"Usage:\n\t./philo nb_philo time_2_die time_2_eat \
time_2_sleep [nbr_eat]"
# define E_DIGIT	"Error:\n\tAll argument must to be only digit."
# define E_INT		"Error:\n\tAll argument must to be integer."
# define E_ARG		"Error:\n\tValue of argument not valid."
# define E_PHILO	"Error:\n\tNumber of philosopher (maxi 200)"
# define E_DIE		"Error:\n\tTime to die not valid."
# define E_EAT		"Error:\n\tTime to eat not valid."
# define E_SLEEP	"Error:\n\tTime to sleep not valid."
# define E_GET_TIME	"Error:\n\tGet time error."

# define FORK "\033[1;92mhas taken a fork\033[0;97m"
# define EAT "\033[1;95mis eating\033[0;97m"
# define SLEEP "\033[1;93mis sleeping\033[0;97m"
# define THINK "\033[1;96mis thinking\033[0;97m"
# define DEAD "\033[1;31mdied\033[0;97m"

/*
 *	Standard library
 */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/types.h>
# include <fcntl.h>

/*
 *	strucutures
 */

typedef struct timeval		t_timeval;

typedef struct s_data
{
	int					nb_philo;
	int					opt_eat;
	unsigned long long	start;
	unsigned long long	ttdie;
	unsigned long long	tteat;
	unsigned long long	ttsleep;
}	t_data;

typedef struct s_philo
{
	int					id;
	int					nb_meal;
	int					pid[200];
	long long			last_change;
	unsigned long long	last_eat;
	sem_t				*fork;
	sem_t				*fork_access;
	sem_t				*print;
	t_data				data;
}	t_philo;

/*
 *	functions
 */

int					ft_perror_exit(char *str_error);

double				ft_min(double a, double b);
double				ft_max(double a, double b);

char				ft_isdigit(int c);

unsigned long long	ft_microtime(void);
unsigned long long	ft_militomicro(unsigned long long miliseconde);
unsigned long long	ft_microtomili(unsigned long long microseconde);

void				ft_eat(t_philo *philo);
void				ft_exec(t_philo *philo);
void				ft_loop(t_philo *philo);
void				ft_think(t_philo *philo);
void				ft_sleep(t_philo *philo);
void				ft_schedule(t_philo *philo);
void				ft_close_semaphore(t_philo *philo);
void				ft_init(t_philo *philo, int ac, char **av);
void				ft_write(const char *status, t_philo *philo);
void				ft_usleep(unsigned long long microseconde);

#endif
