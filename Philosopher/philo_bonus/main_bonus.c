/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:06:53 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/07/30 10:17:52 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 *	philosopher_bonus
 * </summary>
 *
 * <description>
 *	philosopher_bonus is a program to learn about the process and the semaphore.
 *	The aim of the program is simply. Each philo has a fork at this right side
 *	and all philo around a table. Each philo nead two forks to eat, after eating 
 *	there spleeping and after there thinking. And asap there could toke a fork
 *	there ate again. If one philo pass time to die without eating he die and the 
 *	program finish directly.
 *	the program take 3 or 4 parameters:
 *		- number of philosopher (max 200)
 *		- time to die (from two start eating)
 *		- time to eat
 *		- time to sleep
 *		- number of eating (optional)
 * </description>
 *
 * <param type="int" name="argc">number of arguments</param>
 * <param type="char **" name="argv">list of integer to sort</param>
 *
 * <return>
 *	0 in success or 1 in error.
 * </return>
 *
 */

int	main(int argc, char **argv)
{
	t_philo	philo;

	memset(&philo, 0, sizeof(philo));
	if (argc < 5 || argc > 6)
		ft_perror_exit(E_USAGE);
	ft_init(&philo, argc, argv);
	ft_close_semaphore(&philo);
	ft_exec(&philo);
	exit(EXIT_SUCCESS);
}
