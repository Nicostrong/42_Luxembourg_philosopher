/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:07:17 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/10/30 09:02:59 by nfordoxc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 * 	void	sleep_process(t_philo *philo)
 * </summary>
 *
 * <description>
 * 	sleep_process is the child process, it's simulate the sleep time.
 * 	Like this, after waiting time to sleep, the child process exit and the 
 * 	parent proces can execute the next.
 * </description>
 *
 * <param type="t_philo *" name="philo">philo structure</param>
 *
 * <return>
 * 	1
 * </return>
 *
 */

static void	sleep_process(t_philo *philo)
{
	ft_usleep(philo->data.ttsleep);
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
 *  thinking and update the time of the next change.
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
	ft_write(THINK, philo);
	philo->last_change = ft_microtime();
}

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 * 	void	ft_sleep(t_philo *philo)
 * </summary>
 *
 * <description>
 * 	ft_sleep is the runtine to manage the sleeping part of each philosophers.
 * 	child process => wait time to sleep and exit.
 * 	parent process => check die and print think
 * </description>
 *
 * <param type="t_philo *" name="philo">philo structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */

void	ft_sleep(t_philo *philo)
{
	int	pid;

	pid = fork();
	if (pid)
		loop_process(philo, pid);
	else
		sleep_process(philo);
}
