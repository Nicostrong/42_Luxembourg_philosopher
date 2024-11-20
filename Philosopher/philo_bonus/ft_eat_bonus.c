/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:05:45 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/10/30 08:59:30 by nfordoxc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 * 	void	eat_process(t_philo *philo)
 * </summary>
 *
 * <description>
 * 	eat_process is the child process, it's simulate the eat time.
 * 	Like this, after waiting time to eat, the child process exit and the 
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

static void	eat_process(t_philo *philo)
{
	ft_usleep(philo->data.tteat);
	sem_post(philo->fork);
	sem_post(philo->fork);
	sem_post(philo->fork_access);
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
 * 	process kill the child process, unblock the semaphore and return the id of 
 * 	the philo who's died.
 * 	If the child process is ending, the parent process can pass to the next step
 *  sleeping and update the time of the next change, and increase the number of 
 * 	meal of this philosopher.
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
	ft_write(SLEEP, philo);
	philo->last_change = ft_microtime();
	philo->nb_meal++;
}

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 * 	void	ft_eat(t_philo *philo)
 * </summary>
 *
 * <description>
 * 	ft_eat is the runtine to manage the eating part of each philosophers.
 * 	child process => wait time to eat and unlock all semaphore.
 * 	parent process => check die and print sleep
 * </description>
 *
 * <param type="t_philo *" name="philo">philo structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */

void	ft_eat(t_philo *philo)
{
	int	pid;

	pid = fork();
	if (pid)
		loop_process(philo, pid);
	else
		eat_process(philo);
	if (philo->nb_meal == philo->data.opt_eat)
		exit(EXIT_SUCCESS);
}
