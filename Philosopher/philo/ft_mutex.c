/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:05:54 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/07/25 10:28:46 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * <cat>philosopher</cat>
 *
 * <summary>
 * 	int	ft_init_global_mutex(t_data *data)
 * </summary>
 *
 * <description>
 * 	ft_init_global_mutex initialise all global mutex on the struct data.
 * </description>
 *
 * <param type="t_data *" name="data">data structure</param>
 *
 * <return>
 * 	1 if all right or exit faillure.
 * </return>
 *
 */

int	ft_init_global_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->m_print, NULL))
		return (ft_perror_exit(E_MUTEX, data));
	if (pthread_mutex_init(&data->m_finish, NULL))
	{
		pthread_mutex_destroy(&data->m_print);
		return (ft_perror_exit(E_MUTEX, data));
	}
	if (pthread_mutex_init(&data->m_all_eating, NULL))
	{
		pthread_mutex_destroy(&data->m_finish);
		pthread_mutex_destroy(&data->m_print);
		return (ft_perror_exit(E_MUTEX, data));
	}
	return (1);
}

/*
 * <cat>philosopher</cat>
 *
 * <summary>
 * 	int	ft_init_thread_mutex(t_data *data)
 * </summary>
 *
 * <description>
 * 	ft_init_thread_mutex initialise all mutex on the struct for each philo.
 * </description>
 *
 * <param type="t_data *" name="data">data structure</param>
 *
 * <return>
 * 	1 if all right or exit faillure.
 * </return>
 *
 */

int	ft_init_thread_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->philo[i].m_fork, NULL) || \
				pthread_mutex_init(&data->philo[i].m_last_meal, NULL) || \
				pthread_mutex_init(&data->philo[i].m_nb_meal, NULL))
		{
			while (--i >= 0)
			{
				pthread_mutex_destroy(&data->philo[i].m_fork);
				pthread_mutex_destroy(&data->philo[i].m_last_meal);
				pthread_mutex_destroy(&data->philo[i].m_nb_meal);
			}
			ft_clean_global_mutex(data);
			return (ft_perror_exit(E_MUTEX, NULL));
		}
	}
	return (1);
}
