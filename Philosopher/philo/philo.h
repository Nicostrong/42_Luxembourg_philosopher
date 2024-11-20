/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:07:05 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/07/25 12:39:54 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*
 *	Define
 */

# define E_USAGE	"Usage:\n\t./philo nb_philo time_2_die time_2_eat \
time_2_sleep [nbr_eat]"
# define E_DIGIT	"Error:\n\tAll argument must to be only digit."
# define E_INT		"Error:\n\tAll argument must to be integer."
# define E_ARG		"Error:\n\tValue of argument not valid."
# define E_PH_DIE	"Error:\n\tNumber of philosopher (maxi 200) or time 2 die."
# define E_ALLOC	"Error:\n\tAlloc memory error."
# define E_MUTEX	"Error:\n\tMutex error."
# define E_THREAD	"Error:\n\tThread error."
# define E_JOIN_TH	"Error:\n\tThread join error."
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
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

/*
 *	strucutures
 */

typedef struct s_philo
{
	int				id;
	int				nb_meal;
	long int		last_meal;
	pthread_t		t_id;
	pthread_mutex_t	m_fork;			// protection of fork
	pthread_mutex_t	m_last_meal;	// protection for last_meal
	pthread_mutex_t	m_nb_meal;		// protection for nb_meal
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				opt_eat;
	int				all_eating;
	int				stop;
	long int		start_time;
	pthread_t		t_dead;			// thread for die
	pthread_mutex_t	m_print;		// protection for printing message
	pthread_mutex_t	m_finish;		// protection of stop variable
	pthread_mutex_t	m_all_eating;	// protection for all eating variable
	t_philo			*philo;
}	t_data;

/*
 *	ft_check_args.c
 */

int			ft_read_args(int ac, char **args, t_data *data);
int			ft_check_args(char **array);

/*
 *	ft_exit.c
 */

int			ft_perror_exit(char *str_error, t_data *data);

/*
 *	ft_runtine.c
 */

void		ft_routine(t_philo *philo);

/*
 *	ft_mutex.c
 */

int			ft_init_global_mutex(t_data *data);
int			ft_init_thread_mutex(t_data *data);

/*
 *	ft_inti_thread.c
 */

void		ft_init_thread(t_data *data);

/*
 *	ft_check_die.c
 */

void		*ft_dead_runtine(void *arg);

/*
 *	ft_utils.c
 */

long int	ft_get_time(t_data *data);
void		ft_print_fork(t_philo *philo);
void		ft_clean_thread_mutex(t_data *data);
void		ft_clean_global_mutex(t_data *data);
void		ft_write(long int timestamp, int id, \
	const char *status, t_data *data);

#endif