/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:03:19 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/10/30 09:03:37 by nfordoxc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
 * <cat>philosopher_bonus</cat>
 *
 * <summary>
 * 	void	ft_write(const char *status, t_data *data)
 * </summary>
 *
 * <description>
 * 	ft_write print on screen the status of each philo on the stdoutput.
 * 	format : [time on 6 digit] [id philo] [status]
 * </description>
 *
 * <param type="const char *" name="status">status of philosopher</param>
 * <param type="t_data *" name="data">data structure</param>
 *
 * <return>
 * 	void.
 * </return>
 *
 */

void	ft_write(const char *status, t_philo *philo)
{
	unsigned long long	time;

	time = ft_microtomili(ft_microtime() - philo->data.start);
	sem_wait(philo->print);
	printf("%6llu\t%d\t%s\n", time, philo->id, status);
	sem_post(philo->print);
}
