/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_runtine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:15:55 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/07/25 12:41:59 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * <cat>philosopher</cat>
 *
 * <summary>
 * 	void	ft_sleep_think_time(t_philo *philo)
 * </summary>
 *
 * <description>
 * 	ft_sleep_think_time print the sleep status and wait time to sleep and print
 * 	think status.
 * </description>
 *
 * <param type="t_philo *" name="philo">philo structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */

static void	ft_sleep_think_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_print);
	ft_write(ft_get_time(philo->data), philo->id, SLEEP, philo->data);
	pthread_mutex_unlock(&philo->data->m_print);
	if (philo->data->ttsleep > philo->data->ttdie)
		usleep((philo->data->ttdie * 2) * 1000);
	else
		usleep(philo->data->ttsleep * 1000);
	pthread_mutex_lock(&philo->data->m_print);
	ft_write(ft_get_time(philo->data), philo->id, THINK, philo->data);
	pthread_mutex_unlock(&philo->data->m_print);
}

/*
 * <cat>philosopher</cat>
 *
 * <summary>
 * 	void	ft_unlock_fork(t_data *data, int id)
 * </summary>
 *
 * <description>
 * 	ft_unlock_fork unlock each fork in the correct order depend of the id.
 * </description>
 *
 * <param type="t_data *" name="data">data structure</param>
 * <param type="int" name="id">id number of the philosopher</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */

static void	ft_unlock_fork(t_data *data, int id)
{
	int	left_fork;
	int	right_fork;

	left_fork = id;
	right_fork = (id + 1) % data->nb_philo;
	if (left_fork < right_fork)
	{
		pthread_mutex_unlock(&data->philo[right_fork].m_fork);
		pthread_mutex_unlock(&data->philo[left_fork].m_fork);
	}
	else
	{
		pthread_mutex_unlock(&data->philo[left_fork].m_fork);
		pthread_mutex_unlock(&data->philo[right_fork].m_fork);
	}
}

/*
 * <cat>philosopher</cat>
 *
 * <summary>
 * 	void	ft_eat(t_philo *philo)
 * </summary>
 *
 * <description>
 * 	ft_eat check the time of last meal, print the status and increase the number
 * 	of meal.
 * </description>
 *
 * <param type="t_philo *" name="philo">philo structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */

static void	ft_eat(t_philo *philo)
{
	t_data	*data;
	int		id;

	data = philo->data;
	id = philo->id;
	pthread_mutex_lock(&philo->m_last_meal);
	philo->last_meal = ft_get_time(philo->data);
	pthread_mutex_unlock(&philo->m_last_meal);
	pthread_mutex_lock(&philo->data->m_print);
	ft_write(ft_get_time(philo->data), philo->id, EAT, data);
	pthread_mutex_unlock(&philo->data->m_print);
	pthread_mutex_lock(&philo->m_nb_meal);
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->m_nb_meal);
	usleep(data->tteat * 1000);
	ft_unlock_fork(data, id);
}

/*
 * <cat>philosopher</cat>
 *
 * <summary>
 * 	void	ft_take_fork(t_philo *philo)
 * </summary>
 *
 * <description>
 * 	ft_take_fork take all forks and print the status.
 * </description>
 *
 * <param type="t_philo *" name="philo">philo structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */

static void	ft_take_fork(t_philo *philo)
{
	int		left_fork;
	int		right_fork;
	t_data	*data;

	data = philo->data;
	left_fork = philo->id;
	right_fork = (philo->id + 1) % data->nb_philo;
	if (left_fork < right_fork)
	{
		pthread_mutex_lock(&data->philo[left_fork].m_fork);
		ft_print_fork(philo);
		usleep(1000);
		pthread_mutex_lock(&data->philo[right_fork].m_fork);
		ft_print_fork(philo);
	}
	else
	{
		pthread_mutex_lock(&data->philo[right_fork].m_fork);
		ft_print_fork(philo);
		pthread_mutex_lock(&data->philo[left_fork].m_fork);
		ft_print_fork(philo);
	}
}

/*
 * <cat>philosopher</cat>
 *
 * <summary>
 * 	void	ft_routine(t_philo *philo)
 * </summary>
 *
 * <description>
 * 	ft_routine is the main function of the thread of the philosopher.
 * </description>
 *
 * <param type="t_philo *" name="philo">philo structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */

void	ft_routine(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->m_finish);
	while (!data->stop)
	{
		pthread_mutex_unlock(&data->m_finish);
		ft_take_fork(philo);
		ft_eat(philo);
		pthread_mutex_lock(&philo->m_nb_meal);
		if (philo->nb_meal == data->opt_eat)
		{
			pthread_mutex_unlock(&philo->m_nb_meal);
			pthread_mutex_lock(&data->m_all_eating);
			data->all_eating++;
			pthread_mutex_unlock(&data->m_all_eating);
		}
		else
			pthread_mutex_unlock(&philo->m_nb_meal);
		ft_sleep_think_time(philo);
		pthread_mutex_lock(&data->m_finish);
	}
	pthread_mutex_unlock(&data->m_finish);
}
