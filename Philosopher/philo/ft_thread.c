/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:14:47 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/07/25 10:20:41 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * <cat>philosopher</cat>
 *
 * <summary>
 * 	int	ft_one_philo(t_philo *philo)
 * </summary>
 *
 * <description>
 * 	ft_one_philo is the runtime for one philosopher
 * </description>
 *
 * <param type="t_philo *" name="philo">philo structure</param>
 *
 * <return>
 * 	1 if one philo
 * 	0 if more philo.
 * </return>
 *
 */

static int	ft_one_philo(t_philo *philo)
{
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_lock(&philo->data->m_print);
		ft_write(ft_get_time(philo->data), philo->id, FORK, philo->data);
		pthread_mutex_unlock(&philo->data->m_print);
		return (1);
	}
	return (0);
}

/*
 * <cat>philosopher</cat>
 *
 * <summary>
 * 	void	*routine_thread(void *arg)
 * </summary>
 *
 * <description>
 * 	routine_thread is the function executed by each thread.
 * </description>
 *
 * <param type="void *" name="arg">philo structure</param>
 *
 * <return>
 * 	NULL.
 * </return>
 *
 */

static void	*routine_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (ft_one_philo(philo))
		return (NULL);
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->data->m_print);
		ft_write(ft_get_time(philo->data), philo->id, THINK, philo->data);
		pthread_mutex_unlock(&philo->data->m_print);
		usleep(philo->data->tteat * 1000);
	}
	philo->last_meal = philo->data->start_time;
	ft_routine(philo);
	return (NULL);
}

/*
 * <cat>philosopher</cat>
 *
 * <summary>
 * 	void	ft_init_thread(t_data *data)
 * </summary>
 *
 * <description>
 * 	ft_init_thread initialise each thread of philosopher.
 * 	execute each thread with the runtime and wait the end of each thread.
 * </description>
 *
 * <param type="t_data *" name="data">data structure</param>
 * 
 * <return>
 * 	void.
 * </return>
 * 
 */

void	ft_init_thread(t_data *data)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	while (++i < data->nb_philo)
	{
		ret = pthread_create(&data->philo[i].t_id, NULL, \
				&routine_thread, &data->philo[i]);
		if (ret)
			ft_perror_exit(E_THREAD, data);
	}
	pthread_create(&data->t_dead, NULL, &ft_dead_runtine, data);
	pthread_join(data->t_dead, NULL);
	i = -1;
	while (++i < data->nb_philo)
	{
		ret = pthread_join(data->philo[i].t_id, NULL);
		if (ret)
			ft_perror_exit(E_THREAD, data);
	}
}
