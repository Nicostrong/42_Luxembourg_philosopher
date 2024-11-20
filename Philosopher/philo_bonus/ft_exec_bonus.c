/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:06:02 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/10/30 09:00:59 by nfordoxc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 * 	void	ft_exec(t_philo *philo)
 * </summary>
 *
 * <description>
 * 	ft_exec initialise all semaphore and create all process.
 * 	child => runtime for philo.
 * 	parent => check die of philo.
 * </description>
 *
 * <param type="t_philo *" name="philo">philo structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */

void	ft_exec(t_philo *philo)
{
	int	pid;
	int	idx;

	philo->fork = sem_open("/fork", \
			O_CREAT | O_EXCL, S_IRWXG, philo->data.nb_philo);
	philo->fork_access = sem_open("/fork_access", \
			O_CREAT | O_EXCL, S_IRWXG, philo->data.nb_philo / 2);
	philo->print = sem_open("/print", O_CREAT | O_EXCL, S_IRWXG, 1);
	idx = 0;
	while (philo->id++ < philo->data.nb_philo)
	{
		pid = fork();
		if (!pid)
			break ;
		philo->pid[idx++] = pid;
	}
	if (pid)
		ft_loop(philo);
	else
		ft_schedule(philo);
}
