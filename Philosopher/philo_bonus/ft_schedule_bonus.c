/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_schedule_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:07:05 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/10/30 09:02:34 by nfordoxc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 * 	void	ft_schedule(t_philo *philo)
 * </summary>
 *
 * <description>
 * 	ft_scdedule sychronise all philo and run the runtine philo.
 * </description>
 *
 * <param type="t_philo *" name="philo">philo structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */

void	ft_schedule(t_philo *philo)
{
	while (philo->data.start > ft_microtime())
		ft_usleep(1000);
	if (philo->data.ttdie == 0)
		exit(EXIT_SUCCESS);
	while (1)
	{
		ft_think(philo);
		ft_eat(philo);
		ft_sleep(philo);
	}
}
