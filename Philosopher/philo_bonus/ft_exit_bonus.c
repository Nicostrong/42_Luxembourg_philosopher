/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 10:08:11 by nfordoxc          #+#    #+#             */
/*   Updated: 2024/10/30 09:01:14 by nfordoxc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
 * <cat>print</cat>
 *
 * <summary>
 *	void	ft_putstr_fd(char *s, int fd)
 * </summary>
 *
 * <description>
 *	ft_putchar_fd write the string s on the output designed by fd.
 * </description>
 *
 * <param type="char *" name="s">string to print</param>
 * <param type="int" name="fd">number of the file descriptor</param>
 *
 * <return>
 *	void.
 * </return>
 *
 */

static void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
}

/*
 * <cat>print</cat>
 *
 * <summary>
 *	void	ft_putendl_fd(char *s, int fd)
 * </summary>
 *
 * <description>
 *	ft_putendl_fd write the string s on the output designed by fd with '\n'.
 * </description>
 *
 * <param type="char *" name="s">string to print</param>
 * <param type="int" name="fd">number of the file descriptor</param>
 *
 * <return>
 *	void
 * </return>
 *
 */

static void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

/*
 * <cat>philo_bonus</cat>
 *
 * <summary>
 * 	int	ft_perror_exit(char *str_error)
 * </summary>
 *
 * <description>
 * 	ft_perror_exit print an error message on stderror.
 * </description>
 *
 * <param type="char *" name="str_error">string error to print</param>
 *
 * <return>
 * 	exit with code 1.
 * </return>
 *
 */

int	ft_perror_exit(char *str_error)
{
	ft_putendl_fd(str_error, 2);
	exit(EXIT_FAILURE);
}

void	ft_close_semaphore(t_philo *philo)
{
	sem_close(philo->fork);
	sem_close(philo->fork_access);
	sem_close(philo->print);
	sem_unlink("/fork");
	sem_unlink("/fork_access");
	sem_unlink("/print");
}
