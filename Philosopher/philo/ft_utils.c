/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:19:55 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/07/25 12:41:46 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * <cat>philosopher</cat>
 *
 * <summary>
 * 	void	ft_clean_thread_mutex(t_data *data)
 * </summary>
 *
 * <description>
 * 	ft_clean_thread_mutex destroy all mutex on the thread philo.
 * </description>
 *
 * <param type="t_data *" name="data">data structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */

void	ft_clean_thread_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->philo[i].m_fork);
		pthread_mutex_destroy(&data->philo[i].m_last_meal);
		pthread_mutex_destroy(&data->philo[i].m_nb_meal);
	}
}

/*
 * <cat>philosopher</cat>
 *
 * <summary>
 * 	void	ft_clean_global_mutex(t_data *data)
 * </summary>
 *
 * <description>
 * 	ft_clean_global_mutex destroy all mutex on the main structure data.
 * </description>
 *
 * <param type="t_data *" name="data">data structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */

void	ft_clean_global_mutex(t_data *data)
{
	pthread_mutex_destroy(&data->m_all_eating);
	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_destroy(&data->m_finish);
}

/*
 * <cat>philosopher</cat>
 *
 * <summary>
 * 	void	ft_write(long int time, int id, const char *status, t_data *data)
 * </summary>
 *
 * <description>
 * 	ft_write print on screen the status of each philo on the stdoutput.
 * 	format : [time on 6 digit] [id philo] [status]
 * </description>
 *
 * <param type="long int" name="time">timestamp</param>
 * <param type="int" name="id">philo number</param>
 * <param type="const char *" name="status">status of philosopher</param>
 * <param type="t_data *" name="data">data structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */

void	ft_write(long int time, int id, const char *status, t_data *data)
{
	int	time_p;

	time_p = 0;
	pthread_mutex_lock(&data->m_finish);
	if (data->stop == 1)
	{
		pthread_mutex_unlock(&data->m_finish);
		return ;
	}
	pthread_mutex_unlock(&data->m_finish);
	time_p = time - data->start_time;
	printf("%6d\t%d\t%s\n", time_p, id + 1, status);
}

//printf("%d %d %s\n", time_p, id + 1, status);

/*
 * <cat>philosopher</cat>
 *
 * <summary>
 * 	void	ft_print_fork(t_philo *philo)
 * </summary>
 *
 * <description>
 * 	ft_print_fork print a message when a fork is taken.
 * </description>
 *
 * <param type="t_philo *" name="philo">philo structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */

void	ft_print_fork(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->m_print);
	ft_write(ft_get_time(philo->data), philo->id, FORK, data);
	pthread_mutex_unlock(&data->m_print);
}

/*
 * <cat>philosopher</cat>
 *
 * <summary>
 * 	long int	ft_get_time(t_data *data)
 * </summary>
 *
 * <description>
 * 	ft_get_time return the current time in microsecond.
 * </description>
 *
 * <param type="t_data *" name="data">data structure</param>
 *
 * <return>
 * 	the current time in microsecond.
 * </return>
 *
 */

long int	ft_get_time(t_data *data)
{
	struct timeval	tv;
	long int		time;

	if (gettimeofday(&tv, NULL) == -1)
		return (ft_perror_exit(E_GET_TIME, data));
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}
