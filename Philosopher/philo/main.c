/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:06:02 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/07/25 11:39:17 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * <cat>philosopher</cat>
 *
 * <summary>
 *	philosopher
 * </summary>
 *
 * <description>
 *	philosopher is a program to learn about the threads and the mutex. The aim 
 *	of the program is simply. Each philo has a fork at this right side and all
 *	philo around a table. Each philo nead two forks to eat, after eating there 
 *	spleeping and after there thinking. And asap there could toke a fork there
 *	ate again. If one philo pass time to die without eating he die and the 
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

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (!ft_check_args(av))
		{
			ft_read_args(ac, av, &data);
			ft_init_global_mutex(&data);
			ft_init_thread_mutex(&data);
			data.start_time = ft_get_time(&data);
			ft_init_thread(&data);
			ft_clean_thread_mutex(&data);
			ft_clean_global_mutex(&data);
			free(data.philo);
			return (0);
		}
		return (1);
	}
	return (ft_perror_exit(E_USAGE, NULL));
}
