/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:06:38 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/10/30 09:02:22 by nfordoxc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 * 	void	ft_organize(t_philo *philo, int id_philo_dead)
 * </summary>
 *
 * <description>
 * 	ft_organize kill all child process, wait all ending patent process and print
 *  dead.
 * </description>
 *
 * <param type="t_philo *" name="philo">philo structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */

static void	ft_organize(t_philo *philo, int id_philo_dead)
{
	int	idx;

	idx = -1;
	while (++idx < philo->data.nb_philo)
		kill(philo->pid[idx], SIGTERM);
	while (philo->id--)
		waitpid(-1, NULL, 0);
	sem_wait(philo->print);
	printf("\033[1;31m%llu %d died\033[0;97m\n",
		ft_microtomili(ft_microtime() - philo->data.start),
		id_philo_dead / 256);
	sem_post(philo->print);
}

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 * 	void	ft_loop(t_philo *philo)
 * </summary>
 *
 * <description>
 * 	ft_loop is a parent of main process, it checking if one philo is dead.
 * 	If one philo is dead, it print dead and close all semaphore.
 * </description>
 *
 * <param type="t_philo *" name="philo">philo structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */

void	ft_loop(t_philo *philo)
{
	int	number_philo_died;

	philo->id--;
	while (philo->id--)
	{
		waitpid(-1, &number_philo_died, 0);
		if (number_philo_died)
		{
			ft_organize(philo, number_philo_died);
			break ;
		}
	}
	ft_close_semaphore(philo);
}
