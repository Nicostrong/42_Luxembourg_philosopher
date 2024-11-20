/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_think_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:07:29 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/10/30 09:03:25 by nfordoxc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 * 	void	think_process(t_philo *philo)
 * </summary>
 *
 * <description>
 * 	think_process is the child process, it locks the semaphore for eating and 
 * 	exit.
 *  The parent proces can execute the next.
 * </description>
 *
 * <param type="t_philo *" name="philo">philo structure</param>
 *
 * <return>
 * 	1
 * </return>
 *
 */

static void	think_process(t_philo *philo)
{
	sem_wait(philo->fork_access);
	sem_wait(philo->fork);
	sem_wait(philo->fork);
	exit(EXIT_SUCCESS);
}

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 * 	void	loop_process(t_philo *philo, int pid)
 * </summary>
 *
 * <description>
 * 	loop_process is the parent process. The parent process wait the end of the 
 * 	child process, check if the philo is died. If the philo is died, the parent
 * 	process kill the child process and return the id of the philo who's died.
 * 	If the child process is ending, the parent process can pass to the next step
 *  eating and update the time of the next change and next_meal.
 * </description>
 *
 * <param type="t_philo *" name="philo">philo structure</param>
 *
 * <return>
 * 	1
 * </return>
 *
 */

static void	loop_process(t_philo *philo, int pid)
{
	while (1)
	{
		if (waitpid(pid, NULL, WNOHANG))
			break ;
		if (ft_microtime() - philo->last_eat > philo->data.ttdie)
		{
			kill(pid, SIGTERM);
			exit(philo->id);
		}
		ft_usleep(1000);
	}
	ft_write(FORK, philo);
	ft_write(FORK, philo);
	ft_write(EAT, philo);
	philo->last_change = ft_microtime();
	philo->last_eat = philo->last_change;
}

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 * 	void	ft_think(t_philo *philo)
 * </summary>
 *
 * <description>
 * 	ft_think is the runtine to manage the think part of each philosophers.
 * 	child process => think (cath semaphore for taken fork)
 * 	parent process => check die and print take fork 2* and eat
 * </description>
 *
 * <param type="t_philo *" name="philo">philo structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */

void	ft_think(t_philo *philo)
{
	int	pid;

	pid = fork();
	if (pid)
		loop_process(philo, pid);
	else
		think_process(philo);
}
