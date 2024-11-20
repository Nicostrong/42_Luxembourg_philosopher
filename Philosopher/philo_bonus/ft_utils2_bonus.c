/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:07:41 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/07/29 14:10:44 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 * 	unsigned long long	ft_microtime(void)
 * </summary>
 *
 * <description>
 * 	ft_microtime get the timestamp actual and return this time in microsecondes.
 * </description>
 *
 * <param type="void" name=""></param>
 *
 * <return>
 * 	the timestamp in microseconde.
 * </return>
 *
 */

unsigned long long	ft_microtime(void)
{
	t_timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000000ull + now.tv_usec);
}

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 * 	void	ft_usleep(unsigned long long microseconde)
 * </summary>
 *
 * <description>
 * 	ft_usleep is my function of usleep. It's suspending a program for x 
 * 	microsecondes.
 * </description>
 *
 * <param type="unsigned long long" name="microseconde">time to sleep</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */

void	ft_usleep(unsigned long long microseconde)
{
	microseconde += ft_microtime();
	while (microseconde > ft_microtime())
		usleep(1000);
}

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 * 	unsigned long long	ft_microtomili(unsigned long long microseconde)
 * </summary>
 *
 * <description>
 * 	ft_microtomili convert a time in microseconde to miliseconde.
 * </description>
 *
 * <param type="unsigned long long" name="microseconde">time to convert</param>
 *
 * <return>
 * 	the time in miliseconde.
 * </return>
 *
 */

unsigned long long	ft_microtomili(unsigned long long microseconde)
{
	return (microseconde / 1000);
}

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 * 	unsigned long long	ft_militomicro(unsigned long long miliseconde)
 * </summary>
 *
 * <description>
 * 	ft_militomicro convert a time in miliseconde to microseconde.
 * </description>
 *
 * <param type="unsigned long long" name="miliseconde">time to convert</param>
 *
 * <return>
 * 	the time in microseconde.
 * </return>
 *
 */

unsigned long long	ft_militomicro(unsigned long long miliseconde)
{
	return (miliseconde * 1000);
}
