/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_die.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:23:48 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/07/25 12:45:17 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * <cat>philosopher</cat>
 *
 * <summary>
 * 	int	ft_check_all_eating(t_data *data)
 * </summary>
 *
 * <description>
 * 	ft_check_all_eating check if all philosophers have eating enought.
 * <description>
 *
 * <param type="t_data *" name="data">data structure</param>
 *
 * <return>
 * 	1 if all philosopher have eating enought
 * 	0 if not.
 * </return>
 *
 */

static int	ft_check_all_eating(t_data *data)
{
	pthread_mutex_lock(&data->m_all_eating);
	if (data->nb_philo == data->all_eating)
	{
		pthread_mutex_unlock(&data->m_all_eating);
		usleep(data->tteat * 1000);
		pthread_mutex_lock(&data->m_finish);
		data->stop = 1;
		pthread_mutex_unlock(&data->m_finish);
		return (1);
	}
	else
		pthread_mutex_unlock(&data->m_all_eating);
	return (0);
}

/*
 * <cat>philosopher</cat>
 *
 * <summary>
 * 	void	ft_check_is_die(t_philo *philo)
 * </summary>
 *
 * <description>
 * 	ft_check_is_die check if the philosopher is died.
 * <description>
 *
 * <param type="t_philo *" name="philo">philo structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */

static void	ft_check_is_die(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&philo->m_last_meal);
	if (ft_get_time(data) - philo->last_meal >= data->ttdie)
	{
		pthread_mutex_unlock(&philo->m_last_meal);
		pthread_mutex_lock(&data->m_print);
		ft_write(ft_get_time(data), philo->id, DEAD, data);
		pthread_mutex_unlock(&data->m_print);
		pthread_mutex_lock(&data->m_finish);
		data->stop = 1;
		pthread_mutex_unlock(&data->m_finish);
		return ;
	}
	pthread_mutex_unlock(&philo->m_last_meal);
}

/*
 * <cat>philosopher</cat>
 *
 * <summary>
 * 	void	*ft_dead_runtine(void *arg)
 * </summary>
 *
 * <description>
 * 	ft_dead_runtine
 * </description>
 *
 * <param type="t_philo *" name="philo">philo structure</param>
 *
 * <return>
 * 	NULL.
 * </return>
 *
 */

void	*ft_dead_runtine(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	usleep(data->ttdie * 1000);
	pthread_mutex_lock(&data->m_finish);
	while (!data->stop)
	{
		pthread_mutex_unlock(&data->m_finish);
		i = -1;
		while (++i < data->nb_philo)
			ft_check_is_die(&data->philo[i]);
		if (ft_check_all_eating(data))
			return (NULL);
		pthread_mutex_lock(&data->m_finish);
	}
	pthread_mutex_unlock(&data->m_finish);
	return (NULL);
}
